//
// Created by vogje01 on 21/12/2022.
// Copyright 2022, 2023 Jens Vogt
//
// This file is part of aws-mock.
//
// aws-mock is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// aws-mock is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with aws-mock.  If not, see <http://www.gnu.org/licenses/>.

#ifndef AWSMOCK_CORE_DIRECTORYWATCHER_H
#define AWSMOCK_CORE_DIRECTORYWATCHER_H

// C standard includes
#include <sys/inotify.h>
#include <unistd.h>

// C++ standard includes
#include <string>
#include <map>
#include <iostream>
#include <utility>

// Poco includes
#include <Poco/BasicEvent.h>
#include <Poco/File.h>
#include <Poco/Thread.h>
#include <Poco/Runnable.h>
#include <Poco/Delegate.h>
#include <Poco/RecursiveDirectoryIterator.h>

// AwsMock includes
#include <awsmock/core/Logger.h>
#include <awsmock/core/LogStream.h>

#define MAX_EVENTS 1024 // Max. number of events to process at one go
#define LEN_NAME 16 // Assuming that the length of the filename won't exceed 16 bytes
#define EVENT_SIZE  (sizeof (struct inotify_event)) // size of one event
#define BUF_LEN     (MAX_EVENTS * (EVENT_SIZE + LEN_NAME)) // buffer to store the data of events
#define ALL_EVENTS	 (IN_CREATE | IN_MODIFY | IN_CLOSE_WRITE | IN_DELETE)

namespace AwsMock::Core {

    enum DirectoryEventType {
      DW_ITEM_ADDED = 1,
      /// A new item has been created and added to the directory.

      DW_ITEM_REMOVED = 2,
      /// An item has been removed from the directory.

      DW_ITEM_MODIFIED = 4,
      /// An item has been modified.

      DW_ITEM_MOVED_FROM = 8,
      /// An item has been renamed or moved. This event delivers the old name.

      DW_ITEM_MOVED_TO = 16
      /// An item has been renamed or moved. This event delivers the new name.
    };

    enum DirectoryEventMask {
      DW_FILTER_ENABLE_ALL = 31,
      /// Enables all event types.

      DW_FILTER_DISABLE_ALL = 0
      /// Disables all event types.
    };

    enum FileType {
      DW_FILE_TYPE = 0,
      DW_DIR_TYPE = 1
    };

    struct DirectoryEvent {

      DirectoryEvent(const std::string &f, DirectoryEventType ev, FileType ft) : item(f), event(ev), type(ft) {}

      /**
       * The directory or file that has been changed.
       */
      const std::string &item;

      /**
       * The kind of event.
       */
      DirectoryEventType event;

      /**
       * The type of file
       */
      FileType type;
    };

    class DirectoryWatcher : public Poco::Runnable {

    public:

      /**
       * Constructor
       */
      explicit DirectoryWatcher(const std::string &rootDir);

      /**
       * Destructor
       */
      ~DirectoryWatcher() override;

      /**
       * Initialization
       */
      void Initialize(const std::string &rootDir);

      /**
       * Main thread running method
       */
      void run() override;

      /**
       * Added event
       */
      Poco::BasicEvent<const DirectoryEvent> itemAdded;

      /**
       * Modified event
       */
      Poco::BasicEvent<const DirectoryEvent> itemModified;

      /**
       * Deleted event
       */
      Poco::BasicEvent<const DirectoryEvent> itemDeleted;

    private:

      /**
       * Process a directory watcher event.
       *
       * @param event inotify event
       * @param filePath file path
       */
      void ProcessDir(struct inotify_event *event, const std::string &filePath);

      /**
       * Process a file watcher event.
       *
       * @param event inotify event
       * @param path file path
       */
      void ProcessFile(struct inotify_event *event, const std::string &path);

      /**
       * Returns th file name
       * @param rootDir root directory
       * @param fileName name of the file
       * @return absolute file name
       */
      static std::string GetFilename(const std::string &rootDir, const char *fileName);

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * File descriptor
       */
      int fd = 0;

      /**
       * Running flag
       */
      bool _running = false;

      /**
       * Poll timeout
       */
      int _timeout = 1000;

      /**
       * Watcher map with absolute file pathes
       */
      std::map<int, std::string> _watcherMap;
    };

} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_DIRECTORYWATCHER_H