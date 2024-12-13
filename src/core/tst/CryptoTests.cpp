//
// Created by vogje01 on 02/06/2023.
//

#ifndef AWSMOCK_CORE_CRYPTO_UTILS_TEST_H
#define AWSMOCK_CORE_CRYPTO_UTILS_TEST_H

// GTest includes
#include <gtest/gtest.h>

// Boost includes
#include <boost/locale.hpp>
#include <boost/spirit/home/support/utf8.hpp>

// Local includes
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/FileUtils.h>

#define TEST_STRING "The quick brown fox jumps over the lazy dog"
#define BASE64_TEST_STRING "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw=="
#define TEST_STRING1 "{\"id\":\"DLI393_9783836272926\",\"artikelTyp\":\"physisch\",\"ursprungsDatei\":\"DLI393/20231113_RheinwerkVerlag_10329_13112023131739313.xml\",\"ursprungsFormat\":\"Onix2.1\",\"standDatum\":\"2023-11-13T00:00:00\",\"lieferantenId\":\"DLI393\",\"produktId\":\"9783836272926\",\"status\":\"aktiv\",\"artikelNummern\":[{\"typ\":\"VVA-Artikelnummer\",\"nummer\":\"459/07292\"},{\"typ\":\"EAN\",\"nummer\":\"9783836272926\"}],\"lieferantenArt\":\"HYBRID\",\"l2000Datenquelle\":30,\"anlieferungsDatum\":\"2023-11-13T13:17:39.3\",\"produktFormAngaben\":{\"produktForm\":\"BB\",\"ausgabe\":{}},\"einbandArt\":\"gebunden\",\"orgaNummer\":\"21359\",\"lieferantenName\":\"Rheinwerk Verlag GmbH\",\"umfaenge\":{\"laenge\":{\"wert\":240,\"einheit\":\"mm\"},\"breite\":{\"wert\":190,\"einheit\":\"mm\"},\"hoehe\":{},\"gewicht\":{},\"durchmesser\":{},\"seitenZahlen\":[{\"typ\":\"11\",\"seitenzahl\":\"824\"}],\"laengeAufgeklappt\":{},\"breiteAufgeklappt\":{}},\"auflage\":{\"nummer\":\"8\",\"erklaerungen\":[{\"text\":\"8. Auflage\"}]},\"titel\":[{\"typ\":\"Haupttitel\",\"ebene\":\"Produkt\",\"sprache\":\"ger\",\"titelText\":\"Adobe Illustrator\",\"untertitelText\":\"Das umfassende Handbuch: Ihr Standardwerk zum Lernen und Nachschlagen – Ausgabe 2020\"}],\"urheber\":[{\"sequenz\":\"1\",\"rolle\":\"A01\",\"name\":\"Monika Gause\",\"nameInvertiert\":\"Gause, Monika\",\"vorname\":\"Monika\",\"nachname\":\"Gause\",\"biografischeAngaben\":[{\"sprache\":\"ger\",\"text\":\"Monika Gause ist freischaffende Kommunikationsdesignerin. Unter der Marke mediawerk gestaltet sie Print- und Bildschirm-Publikationen, erstellt Illustrationen, Animationen und Collagen. Darueber hinaus ist sie als Dozentin und als Software-Trainerin taetig.Auf ihrer Website bietet die Autorin viele nuetzliche Ergaenzungen zu ihrem Buch an: www.vektorgarten.de\"}]}],\"hersteller\":[{\"rolle\":\"01\",\"name\":\"Rheinwerk Verlag\"}],\"herstellungsland\":\"DE\",\"sprachen\":[{\"art\":\"Text\",\"code\":\"ger\"}],\"erscheinungsland\":\"DE\",\"erscheinungsorte\":[\"Bonn\"],\"produktKlassifikationen\":[{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Zeichnen lernen\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Grafik-Design\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Sammelgruppe\",\"version\":\"2.0\",\"kuerzel\":\"41108\"},{\"ebene\":\"HauptKlassifikation\",\"art\":\"BISAC Subject Heading\",\"kuerzel\":\"DES007040\"},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Illustrieren\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Grafik-Software\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Hand-Buch\"}]},{\"ebene\":\"HauptKlassifikation\",\"art\":\"Warengruppe\",\"version\":\"2.0\",\"kuerzel\":\"1635\"},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Mac PC Windows\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Malen\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Thema\",\"version\":\"1.2\",\"kuerzel\":\"2ACG\"},{\"ebene\":\"HauptKlassifikation\",\"art\":\"Thema\",\"version\":\"1.2\",\"kuerzel\":\"UGL\"},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Medien-Gestaltung\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Digitale Illustration\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Kommunikation\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Digital Malen\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Vektorgrafik\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Adobe Illustrator CC 2020\"}]},{\"ebene\":\"Klassifikation\",\"art\":\"Schlagwort\",\"ueberschriften\":[{\"sprache\":\"ger\",\"text\":\"Creative Suite\"}]}],\"produktAnlieferungen\":[{\"lieferantenAngaben\":[{\"lieferanten\":[{\"rolle\":\"01\",\"lieferantenName\":\"Rheinwerk Verlag\"}],\"lieferbarkeit\":\"51\",\"ohnePreis\":false,\"preise\":[{\"steuerwerte\":[{\"typ\":\"01\",\"code\":\"R\"}],\"typ\":\"04\",\"status\":\"02\",\"betrag\":\"59.90\",\"waehrung\":\"EUR\",\"mindestBestellMenge\":1,\"rabattCode\":[{\"typ\":\"02\",\"code\":\"RG1\",\"typName\":\"DLI393\"}],\"merkmale\":[\"gebunden\",\"brutto\",\"verkauf\",\"de\"],\"preisLaender\":{\"inklusiveLaender\":[\"DE\"]}},{\"steuerwerte\":[{\"typ\":\"01\",\"code\":\"R\"}],\"typ\":\"04\",\"status\":\"02\",\"betrag\":\"61.60\",\"waehrung\":\"EUR\",\"mindestBestellMenge\":1,\"merkmale\":[\"at\",\"gebunden\",\"brutto\",\"verkauf\"],\"preisLaender\":{\"inklusiveLaender\":[\"AT\"]}},{\"steuerwerte\":[{\"typ\":\"01\",\"code\":\"R\"}],\"typ\":\"04\",\"status\":\"02\",\"betrag\":\"76.95\",\"waehrung\":\"CHF\",\"mindestBestellMenge\":1,\"merkmale\":[\"ch\",\"gebunden\",\"brutto\",\"verkauf\"],\"preisLaender\":{\"inklusiveLaender\":[\"CH\"]}},{\"steuerwerte\":[{\"typ\":\"01\",\"code\":\"R\"}],\"typ\":\"03\",\"status\":\"02\",\"betrag\":\"55.98\",\"waehrung\":\"EUR\",\"mindestBestellMenge\":1,\"merkmale\":[\"gebunden\",\"verkauf\",\"netto\",\"de\"],\"preisLaender\":{\"inklusiveLaender\":[\"DE\"]}}]}]}],\"publikationsStatus\":{\"status\":\"08\",\"erscheinungsTermine\":[{\"typ\":\"01\",\"datum\":\"20200328\",\"format\":\"00\"},{\"typ\":\"10\",\"datum\":\"20200328\",\"format\":\"00\"}]},\"textAnnotationen\":[{\"textTyp\":\"01\",\"zielGruppen\":[\"00\"],\"text\":[{\"sprache\":\"ger\",\"text\":\"<p>Generationen von Illustrator-Anwendern haben dieses hilfreiche Nachschlagewerk von Monika Gause bereits im Regal stehen. Klar strukturiert und leicht verstaendlich erlaeutert es wirklich alle Werkzeuge und Funktionen und zeigt, wie Sie mit Illustrator CC kreativ arbeiten koennen: Durch die zahlreichen Praxisworkshops koennen Sie die Software direkt selbst anwenden. Fortgeschrittene werden das Buch wegen der vielen Tipps und Tricks und der Erlaeuterungen anspruchsvoller Funktionen wie z.B. 3D-Live-Effekten, Perspektivischen Darstellungen und Erweiterungen durch Skripten zu schaetzen wissen.<br />Ein umfassendes Lern- und Nachschlagewerk fuer jeden Illustrator-Anwender.<br /></p><p><b>Aus dem Inhalt:</b></p><p><ul><li></b>Programmoberflaeche und grundlegende Einstellungen</b></li><li>Die Arbeitsumgebung in Illustrator CC</li><li>Vektorgrafik-Grundlagen</li><li>Arbeiten mit Dokumenten</li></ul><ul><li><b>Objekte erstellen</b></li><li>Geometrische Objekte und Transformationen</li><li>Pfade konstruieren und bearbeiten</li><li>Freihand-Werkzeuge</li><li>Farbe</li><li>Mit Konturen und Pinseln arbeiten</li><li>Verlaeufe und Verlaufsgitter</li></ul><ul><li><b>Objekte organisieren und bearbeiten</b></li><li>Vektorobjekte bearbeiten und kombinieren</li><li>Hierarchische Struktur: Ebenen &amp; Aussehen</li><li>Transparenzen und Masken</li><li>Spezial-Effekte</li></ul><ul><li><b>Spezialobjekte</b></li><li>Text und Typografie</li><li>Diagramme</li><li>Muster, Raster und Schraffuren</li><li>Symbole: Objektkopien organisieren</li><li>Perspektivische Darstellungen und 3D-Live-Effekte</li><li>Mit Pixel- und anderen Fremddaten arbeiten</li></ul><ul><li><b>Ausgabe und Optimierung</b></li><li>Austausch, Weiterverarbeitung, Druck</li><li>Web- und Bildschirmgrafik</li><li>Personalisieren und erweitern</li><li>Plug-ins fuer Illustrator</li></ul></p><p><br /><b>Die Fachpresse zur Vorauflage:</b><br /><br />maclife.de: Der Untertitel ist Programm: Das umfassende Handbuch bietet maximale Information sowohl zum Erlernen der Software als auch zum gezielten Nachschlagen.<br /><br />Akademie Druck + Medien Nord-West e.V.: Das Werk beeindruckt auch erfahrene Pfadfinder mit wissenswerter Vollstaendigkeit.<br /><br /></p>\",\"format\":\"02\"}]},{\"textTyp\":\"04\",\"zielGruppen\":[\"00\"],\"text\":[{\"sprache\":\"ger\",\"text\":\"<br /><br /><strong>&nbsp;&nbsp;Vorwort ... 29</strong><br /><br /><br /><br /><br /><strong>TEIL I&nbsp;&nbsp;Programmoberflaeche und grundlegende Einstellungen ... 31</strong><br /><br /><br /><br /><strong>&nbsp;&nbsp;1.&nbsp;&nbsp;Die Arbeitsumgebung in Illustrator ... 33</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.1 ... Der Arbeitsbereich ... 33<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.2 ... Der Touch-Arbeitsbereich ... 45<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.3 ... Bibliotheken verwenden ... 46<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.4 ... CC-Bibliotheken verwenden ... 48<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.5 ... Der Anwendungsrahmen ... 51<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.6 ... Illustrator beenden ... 54<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.7 ... Abgesicherter Modus ... 55<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;1.8 ... Adobe Bridge ... 56<br /><br /><br /><br /><strong>&nbsp;&nbsp;2.&nbsp;&nbsp;Vektorgrafik-Grundlagen ... 57</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.1 ... Warum Vektorgrafik?  ... 57<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2.2 ... Funktionsweise von Vektorgrafik ... 59<br /><br /><br /><br /><strong>&nbsp;&nbsp;3.&nbsp;&nbsp;Arbeiten mit Dokumenten ... 65</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.1 ... Dokumente erstellen und oeffnen ... 65<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.2 ... Im Dokument navigieren ... 71<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.3 ... Mehrseitige Dokumente mit Zeichenflaechen ... 77<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.4 ... Masseinheiten und Lineale  ... 84<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.5 ... Raster und Hilfslinien ... 88<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.6 ... Widerrufen und wiederherstellen ... 94<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;3.7 ... Dokumente speichern ... 95<br /><br /><br /><br /><br /><strong>TEIL II&nbsp;&nbsp;Objekte erstellen ... 103</strong><br /><br /><br /><br /><strong>&nbsp;&nbsp;4.&nbsp;&nbsp;Geometrische Objekte und Transformationen ... 105</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4.1 ... Form- und Linien-Werkzeuge ... 105<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4.2 ... Interaktive Formen ... 114<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4.3 ... Objekte, Pfade und Punkte auswaehlen ... 118<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4.4 ... Objekte in der Stapelreihenfolge anordnen ... 122<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4.5 ... Objekte gruppieren ... 124<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4.6 ... Objekte bearbeiten ... 125<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4.7 ... Objekte transformieren ... 128<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;4.8 ... Ausrichten und Verteilen ... 144<br /><br /><br /><br /><strong>&nbsp;&nbsp;5.&nbsp;&nbsp;Pfade konstruieren und bearbeiten ... 149</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.1 ... Die Anatomie eines Pfades ... 149<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.2 ... Pfade erstellen ... 150<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.3 ... Mit dem Kurvenzeichner arbeiten ... 160<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.4 ... Punkte und Pfadsegmente auswaehlen ... 161<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.5 ... Freihand-Auswahl mit dem Lasso ... 164<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.6 ... Punkte und Pfadsegmente bearbeiten ... 165<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.7 ... Pfade ergaenzen und kombinieren  ... 174<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;5.8 ... Strategien zum Zeichnen von Vektorpfaden ... 180<br /><br /><br /><br /><strong>&nbsp;&nbsp;6.&nbsp;&nbsp;Freihand-Werkzeuge ... 187</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;6.1 ... Freihand-Linien zeichnen ... 187<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;6.2 ... Natuerlich malen mit dem Borstenpinsel ... 196<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;6.3 ... Flaechen malen mit dem Tropfenpinsel ... 199<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;6.4 ... Objekte intuitiv bearbeiten und  Pfade vereinfachen ... 202<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;6.5 ... Objekte intuitiv deformieren mit den Verfluessigen-Werkzeugen ... 208<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;6.6 ... Objekte mit dem Formgitter bearbeiten ... 212<br /><br /><br /><br /><strong>&nbsp;&nbsp;7.&nbsp;&nbsp;Farbe ... 215</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.1 ... Farbmodelle ... 215<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.2 ... Farbmanagement ... 217<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.3 ... Dokumentfarbmodus ... 222<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.4 ... Farben anwenden und definieren ... 223<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.5 ... Mit Farbfeldern arbeiten ... 228<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.6 ... Farbfelder anwenden ... 237<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.7 ... Farbharmonien erarbeiten ... 241<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.8 ... Mit Adobe-Color-Themen arbeiten ... 245<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.9 ... Farbharmonien anwenden ... 245<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;7.10 ... Farbfilter  ... 263<br /><br /><br /><br /><strong>&nbsp;&nbsp;8.&nbsp;&nbsp;Mit Konturen und Pinseln arbeiten ... 267</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8.1 ... Standard-Konturoptionen ... 267<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8.2 ... Pfeilspitzen ... 270<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8.3 ... Variable Konturstaerken mit dem Breitenwerkzeug ... 271<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8.4 ... Pinselkonturen ... 276<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;8.5 ... Auswahlen auf Farb- und Objektbasis ... 294<br /><br /><br /><br /><strong>&nbsp;&nbsp;9.&nbsp;&nbsp;Verlaeufe und Verlaufsgitter ... 297</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;9.1 ... Verlaeufe ... 297<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;9.2 ... Gitterobjekte -- Verlaufsgitter ... 315<br /><br /><br /><br /><br /><strong>TEIL III&nbsp;&nbsp;Objekte organisieren und bearbeiten ... 329</strong><br /><br /><br /><br /><strong>10.&nbsp;&nbsp;Vektorobjekte bearbeiten und kombinieren ... 331</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10.1 ... Objekte kombinieren ... 331<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10.2 ... Objekte zerteilen -- Pathfinder ... 336<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10.3 ... Formerstellung intuitiv ... 341<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10.4 ... Schweizer Messer: Das Shaper-Werkzeug  ... 343<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10.5 ... Interaktiv malen ... 346<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10.6 ... Linien in Flaechen umwandeln ... 357<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10.7 ... Formen und Objekte ueberblenden ... 362<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;10.8 ... Objekte mit Huellen verzerren ... 371<br /><br /><br /><br /><strong>11.&nbsp;&nbsp;Hierarchische Struktur: Ebenen &amp; Aussehen ... 377</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11.1 ... Ebenen-Grundlagen ... 377<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11.2 ... Mit dem Ebenen-Bedienfeld arbeiten ... 380<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11.3 ... Objekt- und Ziel-Auswahl ... 388<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11.4 ... Objekte mit Schnittmasken formen ... 391<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11.5 ... Mit dem Isolationsmodus in tiefe  Hierarchien vordringen ... 394<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11.6 ... Aussehen-Eigenschaften  ... 396<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11.7 ... Aussehen-Eigenschaften mit der  Pipette uebertragen ... 406<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;11.8 ... Aussehen-Eigenschaften als  Grafikstile speichern ... 407<br /><br /><br /><br /><strong>12.&nbsp;&nbsp;Transparenzen und Masken ... 419</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;12.1 ... Deckkraft und Fuellmethode ... 419<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;12.2 ... Deckkraftmasken ... 430<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;12.3 ... Transparenz-Effekte ... 437<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;12.4 ... Transparenzen reduzieren ... 438<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;12.5 ... Transparenz speichern ... 448<br /><br /><br /><br /><strong>13.&nbsp;&nbsp;Spezial-Effekte ... 451</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;13.1 ... Allgemeines zu Effekten ... 451<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;13.2 ... Konstruktionseffekte ... 454<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;13.3 ... Zeichnerische Effekte ... 461<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;13.4 ... Pixelbasierte Effekte ... 468<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;13.5 ... Special Effects ... 481<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;13.6 ... SVG-Filter ... 485<br /><br /><br /><br /><br /><strong>TEIL IV&nbsp;&nbsp;Text und Typografie ... 487</strong><br /><br /><br /><br /><strong>14.&nbsp;&nbsp;Text und Typografie ... 489</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14.1 ... Textobjekte erzeugen ... 489<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14.2 ... Textobjekte bearbeiten ... 492<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14.3 ... Texte importieren ... 501<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14.4 ... Textinhalte editieren ... 503<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14.5 ... Zeichen formatieren ... 512<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14.6 ... Absaetze formatieren ... 522<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14.7 ... Zeichen- und Absatzformate ... 532<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14.8 ... Mit Texten gestalten ... 535<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;14.9 ... Von Text zu Grafik ... 541<br /><br /><br /><br /><strong>15.&nbsp;&nbsp;Diagramme ... 545</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;15.1 ... Ein Diagramm erstellen ... 545<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;15.2 ... Kreisdiagramme ... 549<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;15.3 ... Saeulen- und Balkendiagramme ... 551<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;15.4 ... Linien- und Flaechendiagramme ... 563<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;15.5 ... Kombinierte Diagramme ... 566<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;15.6 ... Streu- oder Punktdiagramme ... 568<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;15.7 ... Netz- oder Radardiagramme ... 569<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;15.8 ... Diagramme weiterbearbeiten ... 570<br /><br /><br /><br /><strong>16.&nbsp;&nbsp;Muster, Raster und Schraffuren ... 575</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;16.1 ... Fuellmuster verwenden ... 575<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;16.2 ... Eigene Muster entwickeln ... 580<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;16.3 ... Schraffuren und Strukturen mit  anderen Mitteln umsetzen  ... 591<br /><br /><br /><br /><strong>17.&nbsp;&nbsp;Objektkopien organisieren:  Symbole und Globale Bearbeitung ... 593</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;17.1 ... Wie funktionieren Symbole? ... 593<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;17.2 ... Symbole verwalten ... 594<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;17.3 ... Symbol-Werkzeuge ... 599<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;17.4 ... Mit dynamischen Symbolen arbeiten ... 606<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;17.5 ... Eigene Symbole entwickeln ... 608<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;17.6 ... Gleiche Objekte finden und bearbeiten ... 614<br /><br /><br /><br /><strong>18.&nbsp;&nbsp;Perspektivische Darstellungen  und 3D-Live-Effekte ... 617</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;18.1 ... Zeichnungen in Fluchtpunktperspektive anlegen ... 617<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;18.2 ... 3D-Objekte mit den 3D-Effekten erzeugen ... 629<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;18.3 ... Oberflaechen-Mapping ... 643<br /><br /><br /><br /><strong>19.&nbsp;&nbsp;Mit Pixel- und anderen Fremddaten arbeiten ... 651</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;19.1 ... Externe Dateien integrieren ... 652<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;19.2 ... Platzierte Daten verwalten ... 660<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;19.3 ... Bilddaten bearbeiten ... 664<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;19.4 ... Pixeldaten vektorisieren ... 670<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;19.5 ... Der Bildnachzeichner   ... 672<br /><br /><br /><br /><br /><strong>TEIL V&nbsp;&nbsp;Ausgabe und Optimierung ... 687</strong><br /><br /><br /><br /><strong>20.&nbsp;&nbsp;Austausch, Weiterverarbeitung, Druck ... 689</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;20.1 ... Export fuer Layout und Bildbearbeitung ... 689<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;20.2 ... Ausgabe als PDF ... 697<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;20.3 ... Grafiken fuer den Druck vorbereiten ... 700<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;20.4 ... Ausdrucken ... 714<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;20.5 ... Mit Verknuepfungen und Fonts verpacken ... 725<br /><br /><br /><br /><strong>21.&nbsp;&nbsp;Web- und Bildschirmgrafik ... 727</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;21.1 ... Screendesign mit Illustrator ... 727<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;21.2 ... Webformate aus Illustrator speichern ... 733<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;21.3 ... Bildformate: GIF, JPEG und PNG ... 743<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;21.4 ... SVG ... 746<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;21.5 ... Animate (Flash) ... 753<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;21.6 ... Video und Film ... 760<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;21.7 ... Character Animator ... 766<br /><br /><br /><br /><strong>22.&nbsp;&nbsp;Personalisieren und erweitern ... 769</strong><br /><br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;22.1 ... Einstellungen anpassen ... 769<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;22.2 ... Automatisieren mit Aktionen ... 777<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;22.3 ... JavaScript &amp; Co. ... 787<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;22.4 ...  Variablen ... 791<br /><br />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;22.5 ... Erweitern ... 795<br /><br /><br /><br /><strong>23.&nbsp;&nbsp;Plug-ins fuer Illustrator ... 797</strong><br /><br /><br /><strong>&nbsp;&nbsp;Index ... 805</strong><br />\",\"format\":\"02\"}]},{\"textTyp\":\"06\",\"zielGruppen\":[\"00\"],\"text\":[{\"sprache\":\"ger\",\"text\":\"Ein Lehrbuch und Nachschlagewerk, aus dem jede/r Designer/in grossen Nutzen ziehen kann – egal ob Anfaenger, fortgeschritten oder Profi.\",\"format\":\"06\"}],\"quellen\":[{\"sprache\":\"ger\",\"text\":\"rainerklute.de\"}]}],\"imprints\":[{\"name\":\"Rheinwerk Design\",\"empty\":false}],\"kategorien\":[{\"typ\":\"04\",\"code\":\"49019900\"}],\"unterstuetzendeRessourcen\":[{\"typ\":\"01\",\"inhaltForm\":\"03\",\"versionen\":[{\"form\":\"02\",\"versionsEigenschaften\":[{\"typ\":\"01\",\"wert\":\"D502\"}],\"links\":[{\"sprache\":\"ger\",\"link\":\"https://onix.rheinwerk-verlag.de/cover/9783836272926.jpg\",\"markedForDownload\":true}],\"inhaltsDaten\":[{\"typ\":\"17\",\"inhaltsDatum\":{\"datum\":\"20200302\",\"format\":\"00\"}}]}]}]}"
#define TEST_STRING2 "{\"id\":\"DLI393_9783836272926\",\"artikelTyp\":\"physisch\",\"ursprungsDatei\":\"DLI393/20231113_RheinwerkVerlag_10329_13112023131739313.xml\",\"ürsprungsFormat\":\"Onix2.1\",\"standDatum\":\"2023-11-13T00:00:00\",\"lieferantenId\":\"DLI393\",\"produktId\":\"9783836272926\",\"status\":\"aktiv\",\"artikelNummern\":[{\"typ\":\"VVA-Artikelnummer\",\"nummer\":\"459/07292\"},{\"typ\":\"EAN\",\"nummer\":\"9783836272926\"}],\"lieferantenArt\":\"HYBRID\",\"l2000Datenquelle\":30,\"anlieferungsDatum\":\"2023-11-13T13:17:39.3\",\"produktFormAngaben\":{\"produktForm\":\"BB\",\"ausgabe\":{}},\"einbandArt\":\"gebunden\",\"orgaNummer\":\"21359\",\"lieferantenName\":\"Rheinwerk Verlag GmbH\",\"umfaenge\":{\"laenge\":{\"wert\":240,\"einheit\":\"mm\"},\"breite\":{\"wert\":190,\"einheit\":\"mm\"},\"hoehe\":{},\"gewicht\":{},\"durchmesser\":{},\"seitenZahlen\":[{\"typ\":\"11\",\"seitenzahl\":\"824\"}],\"laengeAufgeklappt\":{},\"breiteAufgeklappt\":{}},\"auflage\":{\"nummer\":\"8\",\"erklaerungen\":[{\"text\":\"8. Auflage\"}]},\"titel\":[{\"typ\":\"Haupttitel\",\"ebene\":\"Produkt\",\"sprache\":\"ger\",\"titelText\":\"Adobe Illustrator\",\"untertitelText\":\"Das umfassende Handbuch: Ihr Standardwerk zum Lernen und Nachschlagen – Ausgabe 2020\"}],\"urheber\":[{\"sequenz\":\"1\",\"rolle\":\"A01\",\"name\":\"Monika Gause\",\"nameInvertiert\":\"Gause, Monika\",\"vorname\":\"Monika\",\"nachname\":\"Gause\",\"biografischeAngaben\":[{\"sprache\":\"ger\",\"text\":\"Monika Gause ist freischaffende Kommunikationsdesignerin. Unter der Marke mediawerk gestaltet sie Print- und Bildschirm-Publikationen, erstellt Illustrationen, Animationen und Collagen."
#define MD5_SUM "d41d8cd98f00b204e9800998ecf8427e"
#define MD5_SUM1 "5e39cce4e34eb60f350d1cf2f1098166"
#define MD5_SUM2 "9e107d9d372bb6826bd81d3542a419d6"
#define SHA1_SUM "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12"
#define SHA256_SUM "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592"
#define SHA256_SUM_EMPTY "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
#define SHA256_HMAC_SUM "62025e1d8825e24f50410f8e9b8c40c319f622244baab30265de1d5ee8bf6a19"

namespace AwsMock::Core {
    class CryptoTest : public ::testing::Test {};

    TEST_F(CryptoTest, Md5StringTest) {

        // arrange

        // act
        std::string result = Crypto::GetMd5FromString(TEST_STRING);

        // assert
        EXPECT_STREQ(result.c_str(), MD5_SUM2);
    }

    TEST_F(CryptoTest, Md5String1Test) {

        // arrange
        auto *input = (unsigned char *) malloc(sizeof(TEST_STRING1));
        memcpy(input, TEST_STRING1, sizeof(TEST_STRING1));

        // act
        //std::string utf8_string = boost::spirit::to_utf8<char>(TEST_STRING1);
        std::string utf8_string = boost::locale::conv::to_utf<char>(TEST_STRING1, "Latin1");
        std::string result = Crypto::GetMd5FromString(input);

        // assert
        EXPECT_STREQ(result.c_str(), MD5_SUM1);
    }

    TEST_F(CryptoTest, Md5FileTest) {

        // arrange
        std::string file = FileUtils::CreateTempFile("txt", TEST_STRING);

        // act
        std::string result = Crypto::GetMd5FromFile("/tmp/utf.txt");

        // assert
        EXPECT_TRUE(result == MD5_SUM);
    }

    TEST_F(CryptoTest, Md5DoubleFileTest) {

        // arrange
        const std::string file1 = FileUtils::CreateTempFile("txt", TEST_STRING);
        const std::string file2 = FileUtils::CreateTempFile("txt", TEST_STRING);

        // act
        const std::string result1 = Crypto::GetMd5FromFile(file1);
        const std::string result2 = Crypto::GetMd5FromFile(file2);

        // assert
        EXPECT_TRUE(result1 == result2);
    }


    TEST_F(CryptoTest, Sha1StringTest) {
        // arrange

        // act
        const std::string result = Crypto::GetSha1FromString(TEST_STRING);

        // assert
        EXPECT_EQ(result, SHA1_SUM);
    }

    TEST_F(CryptoTest, Sha1FileTest) {

        // arrange
        const std::string file = FileUtils::CreateTempFile("txt", TEST_STRING);

        // act
        const std::string result = Crypto::GetSha1FromFile(file);

        // assert
        EXPECT_EQ(result, SHA1_SUM);
    }

    TEST_F(CryptoTest, Sha256StringTest) {

        // arrange

        // act
        const std::string result = Crypto::GetSha256FromString(TEST_STRING);

        // assert
        EXPECT_EQ(result, SHA256_SUM);
    }

    TEST_F(CryptoTest, Sha256EmptyStringTest) {

        // arrange

        // act
        const std::string result = Crypto::GetSha256FromString("");

        // assert
        EXPECT_EQ(result, SHA256_SUM_EMPTY);
    }

    TEST_F(CryptoTest, Sha256FileTest) {

        // arrange
        const std::string file = FileUtils::CreateTempFile("txt", TEST_STRING);

        // act
        const std::string result = Crypto::GetSha256FromFile(file);

        // assert
        EXPECT_EQ(result, SHA256_SUM);
    }

    TEST_F(CryptoTest, GetHmacSha256Test) {

        // arrange

        // act
        const std::string result = Crypto::GetHmacSha256FromString("secretKey", TEST_STRING);

        // assert
        EXPECT_EQ(result, "6a7323506a6493e320d27b6eb5c64e722a314e15ddb753c837738e0c174cdb03");
    }

    TEST_F(CryptoTest, Base64EncodeTest) {

        // arrange

        // act
        const std::string result = Crypto::Base64Encode(TEST_STRING);

        // assert
        EXPECT_EQ(result, BASE64_TEST_STRING);
    }

    TEST_F(CryptoTest, Base64DecodeTest) {

        // arrange

        // act
        const std::string result = Crypto::Base64Decode(BASE64_TEST_STRING);

        // assert
        EXPECT_EQ(result, TEST_STRING);
    }

    TEST_F(CryptoTest, Base64Test) {

        // arrange
        const std::string testText = "Base64 hashing";

        // act
        const std::string encrypted = Crypto::Base64Encode(testText);
        const std::string decrypted = Crypto::Base64Decode(encrypted);

        // assert
        EXPECT_TRUE(StringUtils::Equals(testText, decrypted));
    }

    TEST_F(CryptoTest, Aes256KeyText) {

        // arrange
        unsigned char key[CRYPTO_AES256_KEY_SIZE];
        unsigned char iv[CRYPTO_AES256_BLOCK_SIZE];

        // act
        Crypto::CreateAes256Key(key, iv);

        // assert
        EXPECT_TRUE(sizeof(key) / sizeof(key[0]) == CRYPTO_AES256_KEY_SIZE);
        EXPECT_TRUE(sizeof(iv) / sizeof(iv[0]) == CRYPTO_AES256_BLOCK_SIZE);
    }

    TEST_F(CryptoTest, Aes256EncryptionText) {

        // arrange
        const std::string testText = "This is a super secure text";
        const std::string key = "TestKey";
        int len = static_cast<int>(testText.length());

        // act
        unsigned char *result1 = Crypto::Aes256EncryptString((unsigned char *) testText.c_str(), &len, (unsigned char *) key.c_str());
        const unsigned char *result2 = Crypto::Aes256DecryptString(result1, &len, (unsigned char *) key.c_str());

        // assert
        EXPECT_STREQ(reinterpret_cast<const char *>(result2), reinterpret_cast<const char *>(testText.c_str()));
    }

    TEST_F(CryptoTest, GenerateRsaKeyTest) {

        // arrange
        const std::string testText = "This_is_a_super_secure_text";

        // Generate key pair and initialize
        EVP_PKEY *keyPair = Crypto::GenerateRsaKeys(4096);

        // act
        // encrypt
        const std::string encrypted = Crypto::RsaEncrypt(keyPair, testText);

        // decrypt
        const std::string decrypted = Crypto::RsaDecrypt(keyPair, encrypted);

        // assert
        EXPECT_TRUE(StringUtils::Equals(testText, decrypted));
    }

    TEST_F(CryptoTest, GetRsaKeyTest) {

        // arrange
        EVP_PKEY *keyPair = Crypto::GenerateRsaKeys(4096);

        // Generate key pair and initialize
        const std::string publicKey = Crypto::GetRsaPublicKey(keyPair);
        const std::string privateKey = Crypto::GetRsaPrivateKey(keyPair);

        // assert
        EXPECT_TRUE(!publicKey.empty());
        EXPECT_EQ(800, publicKey.size());
        EXPECT_TRUE(!privateKey.empty());
        EXPECT_EQ(4072, privateKey.size());
    }

    TEST_F(CryptoTest, HexEncodeDecodeTest) {

        // arrange
        std::string testString = "This is a test string";

        // act
        const std::string encoded = Crypto::HexEncode(reinterpret_cast<unsigned char *>(testString.data()), testString.length());
        unsigned char *decoded = Crypto::HexDecode(encoded);

        // assert
        EXPECT_STRCASEEQ(testString.c_str(), reinterpret_cast<char *>(decoded));
    }

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_CRYPTO_UTILS_TEST_H