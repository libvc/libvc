# libvc

[vCard](https://tools.ietf.org/html/rfc2426) (the Electronic Business
Card) library.  Fork of libvc, part of the
[Rolo](http://rolo.sourceforge.net/) project, which seems abandoned.

Original read me file provided in README.

## Compilation

    autoreconf -f -i
    ./configure
    make
    make install

Note: if making changes, use

    git update-index --assume-unchanged INSTALL

to avoid automatic changes to INSTALL making it into the git history.
