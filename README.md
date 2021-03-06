QtNote
======
It's just very small Qt app which usually lives in your system tray and allows you to make notes quick way.

QtNote was written as a clone of Tomboy with use of Qt.
It's not so feature rich as Tomboy but light and fast and usually suits all common needs.
Moreover QtNote can work with Tomboy notes and it's not so hard add support of other apps.

Some features:
* Quick access to notes from tray menu
* Internal notes manager to handle multiple notes at once / search notes
* Support for Tomboy notes
* Create notes from selection by hotkey
* Spell checking
* Crossplatform (tested on linux and windows with gcc and Visual C)
* Other: configurable amount of notes in menu. configurable storage path, print note, save note dialog geometry


## Downloads

Check https://github.com/Ri0n/QtNote/releases page for the latest downloads.

Some older releases could be found at https://yadi.sk/d/HbnqnaTN6fwzN.

## Compilation
qmake && make && make install is usually enough.
but if anything went wrong there are some qmake options supported:
<pre>
CONFIG+=
  bundled_singleapp - use bundled qsingleappliction instead of system one
  devel - build in developerment mode
  nokde - don't build kde plugin
  noubuntu - don't build ubuntu integration plugin
  notomboy - don't build tomboy plugin
  nospellcheker - don't build spellchecker plugin

PREFIX=<dir>  (default: /usr, unix only)
DATADIR=<dir> (default: PREXIX/share, unix only)
LIBDIR=<dir>  (default: PREFIX/lib, unix only)
MANDIR=<dir>  (default: DATADIR/man/man1, unix only)
TRANSLATIONSDIR=<dir> (default: DATADIR/qtnote, unix only)
HUNSPELL_DIR=<dir> installation prefix of hunspell (useful on windows)
HUNSPELL_LIB=<dir> lib directory of hunspell in case HUNSPELL_DIR does not suite (useful on windows)
HUNSPELL_INC=<dir> include directory of hunspell in case HUNSPELL_DIR does not suite (useful on windows)
WININST_PREFIX=<dir> installation prefix on windows (ready to pack as portable or for installer)
</pre>

Development:
You can try to start qmake in development mode.

  qmake CONFIG+=devel

this mode forces plugins loader to use application directory to load plugins.

Deployment:
Look at common.pri. It contains some variables you may need to redefine, like PREFIX, LIBDIR and others.
So just pass this variables to qmake:

  qmake PREFIX=/usr


## Windows

The build was last tested with mingw which supplied by qt-5.5 installer.
But previously it was also compilable with msvc.
Find msvc project file in the root directory. Probably it's a little outdeated for now
and should be regenerated by vs qt addon.

## Build DEB/RPM

Check ./admin/{deb,rpm}build.sh scripts. You can start them w/o arguments.

## Internationalization

https://www.transifex.com/projects/p/qtnote/
