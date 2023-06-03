//	MIT License
//
//	Copyright(c) 2017 Thomas Monkman
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.

#ifndef AWSMOCK_CORE_FILEWATCHER_H
#define AWSMOCK_CORE_FILEWATCHER_H

#include <cstdio>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <sys/types.h>
#include <sys/inotify.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <linux/limits.h>
#include <functional>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <utility>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <system_error>
#include <string>
#include <algorithm>
#include <type_traits>
#include <future>
#include <regex>
#include <cstddef>
#include <cstring>
#include <cwchar>
#include <cassert>
#include <cstdlib>
#include <iostream>

namespace AwsMock::Core {

    enum class Event {
      added,
      removed,
      modified,
      renamed_old,
      renamed_new
    };

    template<typename StringType>
    struct IsWChar {
      static constexpr bool value = false;
    };

    template<>
    struct IsWChar<wchar_t> {
      static constexpr bool value = true;
    };

    template<typename Fn, typename... Args>
    struct Invokable {
      static Fn make() {
          return (Fn *) 0;
      }

      template<typename T>
      static T defaultValue() {
          return *(T *) 0;
      }

      static void call(int) {
          make()(defaultValue<Args...>());
      }

      static int call(long value);

      static constexpr bool value = std::is_same<decltype(call(0)), int>::value;
    };

#define _FILEWATCH_TO_STRING(x) #x
#define FILEWATCH_TO_STRING(x) _FILEWATCH_TO_STRING(x)

    [[maybe_unused]] static const char *event_to_string(Event event) {
        switch (event) {
        case Event::added:return FILEWATCH_TO_STRING(Event::added);
        case Event::removed:return FILEWATCH_TO_STRING(Event::removed);
        case Event::modified:return FILEWATCH_TO_STRING(Event::modified);
        case Event::renamed_old:
            return FILEWATCH_TO_STRING(Event:
                                           renamed_old);
        case Event::renamed_new:return FILEWATCH_TO_STRING(Event::renamed_new);
        }
        assert(false);
    }

    template<typename StringType>
    static typename std::enable_if<std::is_same<typename StringType::value_type, wchar_t>::value, bool>::type
    isParentOrSelfDirectory(const StringType &path) {
        return path == L"." || path == L"..";
    }

    template<typename StringType>
    static typename std::enable_if<std::is_same<typename StringType::value_type, char>::value, bool>::type
    isParentOrSelfDirectory(const StringType &path) {
        return path == "." || path == "..";
    }

    /**
    * FileWatch
     *
    * <p> Watches a folder or file, and will notify of changes via function callback.</p>
    */
    template<class StringType>
    class FileWatch {
      typedef typename StringType::value_type C;
      typedef std::basic_string<C, std::char_traits<C>> UnderpinningString;
      typedef std::basic_regex<C, std::regex_traits<C>> UnderpinningRegex;

    public:

      FileWatch(StringType path, UnderpinningRegex pattern, std::function<void(const StringType &file, const Event event_type)> callback) :
          _path(absolute_path_of(path)), _pattern(pattern), _callback(callback), _directory(get_directory(path)) {
          init();
      }

      FileWatch(StringType path, std::function<void(const StringType &file, const Event event_type)> callback) :
          FileWatch<StringType>(path, UnderpinningRegex(_regex_all), callback) {}

      ~FileWatch() {
          destroy();
      }

      FileWatch(const FileWatch<StringType> &other) : FileWatch<StringType>(other._path, other._callback) {}

      FileWatch<StringType> &operator=(const FileWatch<StringType> &other) {
          if (this == &other) {
              return *this;
          }

          destroy();
          _path = other._path;
          _callback = other._callback;
          _directory = get_directory(other._path);
          init();
          return *this;
      }

      /**
       * Const member variables don't let me implement moves nicely, if moves are really wanted std::unique_ptr should be used and move that.
       */
      FileWatch<StringType>(FileWatch<StringType> &&) = delete;
      FileWatch<StringType> &operator=(FileWatch<StringType> &&) & = delete;

    private:
      static constexpr C _regex_all[] = {'.', '*', '\0'};
      static constexpr C _this_directory[] = {'.', '/', '\0'};

      struct PathParts {
        PathParts(StringType directory, StringType filename) : directory(directory), filename(filename) {}
        StringType directory;
        StringType filename;
      };
      const StringType _path;

      UnderpinningRegex _pattern;

      static constexpr std::size_t _buffer_size = {1024 * 256};

      // only used if watch a single file
      StringType _filename;

      std::function<void(const StringType &file, const Event event_type)> _callback;

      std::thread _watch_thread;

      std::condition_variable _cv;
      std::mutex _callback_mutex;
      std::vector<std::pair<StringType, Event>> _callback_information;
      std::thread _callback_thread;

      std::promise<void> _running;
      std::atomic<bool> _destroy = {false};
      bool _watching_single_file = {false};

      struct FolderInfo {
        int folder;
        int watch;
      };

      FolderInfo _directory;

      const std::uint32_t _listen_filters = IN_MODIFY | IN_CREATE | IN_DELETE;

      const static std::size_t event_size = (sizeof(struct inotify_event));

      void init() {
          _callback_thread = std::thread([this]() {
            try {
                callback_thread();
            } catch (...) {
                try {
                    _running.set_exception(std::current_exception());
                }
                catch (...) {
                } // set_exception() may throw too
            }
          });

          _watch_thread = std::thread([this]() {
            try {
                monitor_directory();
            } catch (...) {
                try {
                    _running.set_exception(std::current_exception());
                }
                catch (...) {
                } // set_exception() may throw too
            }
          });

          std::future<void> future = _running.get_future();
          future.get(); //block until the monitor_directory is up and running
      }

      void destroy() {
          _destroy = true;
          _running = std::promise<void>();

          inotify_rm_watch(_directory.folder, _directory.watch);

          _cv.notify_all();
          _watch_thread.join();
          _callback_thread.join();

          close(_directory.folder);
      }

      const PathParts split_directory_and_file(const StringType &path) const {
          const auto predict = [](C character) {
            return character == C('/');
          };

          UnderpinningString path_string = path;
          const auto pivot = std::find_if(path_string.rbegin(), path_string.rend(), predict).base();
          //if the path is something like "test.txt" there will be no directory part, however we still need one, so insert './'
          const StringType directory = [&]() {
            const auto extracted_directory = UnderpinningString(path_string.begin(), pivot);
            return (extracted_directory.size() > 0) ? extracted_directory : UnderpinningString(_this_directory);
          }();
          const StringType filename = UnderpinningString(pivot, path_string.end());
          return PathParts(directory, filename);
      }

      bool pass_filter(const UnderpinningString &file_path) {
          if (_watching_single_file) {
              const UnderpinningString extracted_filename = {split_directory_and_file(file_path).filename};
              //if we are watching a single file, only that file should trigger action
              return extracted_filename == _filename;
          }
          return std::regex_match(file_path, _pattern);
      }

      bool is_file(const StringType &path) const {
          struct stat statbuf = {};
          if (stat(path.c_str(), &statbuf) != 0) {
              throw std::system_error(errno, std::system_category());
          }
          return S_ISREG(statbuf.st_mode);
      }

      FolderInfo get_directory(const StringType &path) {
          const auto folder = inotify_init();
          if (folder < 0) {
              throw std::system_error(errno, std::system_category());
          }

          _watching_single_file = is_file(path);

          const StringType watch_path = [this, &path]() {
            if (_watching_single_file) {
                const auto parsed_path = split_directory_and_file(path);
                _filename = parsed_path.filename;
                return parsed_path.directory;
            } else {
                return path;
            }
          }();

          const auto watch = inotify_add_watch(folder, watch_path.c_str(), IN_MODIFY | IN_CREATE | IN_DELETE);
          if (watch < 0) {
              throw std::system_error(errno, std::system_category());
          }
          return {folder, watch};
      }

      void monitor_directory() {
          std::vector<char> buffer(_buffer_size);

          _running.set_value();
          while (!_destroy) {
              const auto length = read(_directory.folder, static_cast<void *>(buffer.data()), buffer.size());
              if (length > 0) {
                  int i = 0;
                  std::vector<std::pair<StringType, Event>> parsed_information;
                  while (i < length) {
                      struct inotify_event *event = reinterpret_cast<struct inotify_event *>(&buffer[i]); // NOLINT
                      if (event->len) {
                          const UnderpinningString changed_file{event->name};
                          if (pass_filter(changed_file)) {
                              if (event->mask & IN_CREATE) {
                                  parsed_information.emplace_back(StringType{changed_file}, Event::added);
                              } else if (event->mask & IN_DELETE) {
                                  parsed_information.emplace_back(StringType{changed_file}, Event::removed);
                              } else if (event->mask & IN_MODIFY) {
                                  parsed_information.emplace_back(StringType{changed_file}, Event::modified);
                              }
                          }
                      }
                      i += event_size + event->len;
                  }
                  //dispatch callbacks
                  {
                      std::lock_guard<std::mutex> lock(_callback_mutex);
                      _callback_information.insert(_callback_information.end(), parsed_information.begin(), parsed_information.end());
                  }
                  _cv.notify_all();
              }
          }
      }

      static StringType absolute_path_of(const StringType &path) {
          char buf[PATH_MAX];
          const char *str = buf;
          struct stat stat{};
          mbstate_t state;

          realpath((const char *) path.c_str(), buf);
          ::stat((const char *) path.c_str(), &stat);

          if (stat.st_mode & S_IFREG || stat.st_mode & S_IFLNK) {
              size_t len = strlen(buf);

              for (size_t i = len - 1; i >= 0; i--) {
                  if (buf[i] == '/') {
                      buf[i] = '\0';
                      break;
                  }
              }
          }

          if (IsWChar<C>::value) {
              size_t needed = mbsrtowcs(nullptr, &str, 0, &state) + 1;
              StringType s;

              s.reserve(needed);
              mbsrtowcs((wchar_t *) &s[0], &str, s.size(), &state);
              return s;
          }
          return StringType{buf};
      }

      void callback_thread() {
          while (!_destroy) {
              std::unique_lock<std::mutex> lock(_callback_mutex);
              if (_callback_information.empty() && !_destroy) {
                  _cv.wait(lock, [this] { return _callback_information.size() > 0 || _destroy; });
              }
              decltype(_callback_information) callback_information = {};
              std::swap(callback_information, _callback_information);
              lock.unlock();

              for (const auto &file : callback_information) {
                  if (_callback) {
                      try {
                          _callback(file.first, file.second);
                      }
                      catch (const std::exception &) {
                      }
                  }
              }
          }
      }
    };

    template<class StringType> constexpr typename FileWatch<StringType>::C FileWatch<StringType>::_regex_all[];
    template<class StringType> constexpr typename FileWatch<StringType>::C FileWatch<StringType>::_this_directory[];
}
#endif