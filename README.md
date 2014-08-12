# pacman4console.debian

This repository contains the **Debian packaging files** for the game
pacman4console (_console based pacman game_).

If you're after the game pacman4console itself, [go to it's homepage][home]

![screen](https://sites.google.com/site/doctormike/pacman-1-1.png)

## Debian Packaging

### Structure

* [**pacman4console on Debian Package Tracking System**][package]

This package is maintained on a Git repository through some important branches.

| branch                                                                            | role |
| --------------------------------------------------------------------------------- | ---- |
| [**debian**](https://github.com/alexdantas/pacman4console.debian/tree/debian)            | pacman4console _and_ the debian package source code (`debian` directory) |
| [**upstream**](https://github.com/alexdantas/pacman4console.debian/tree/upstream)        | Everything that was on the original upstream tarball (`orig.tar.gz`) |
| [**pristine-tar**](https://github.com/alexdantas/pacman4console.debian/tree/pristine-tar)| Debian original tarball |
| [**readme**](https://github.com/alexdantas/pacman4console.debian/tree/readme)            | This single file, explaining all that |


### Getting Started

To start working on this package, clone this repository
 [along with all branches](http://stackoverflow.com/a/72156):

```bash
# Cloning the entire repository
$ git clone https://github.com/alexdantas/pacman4console.debian

# For now you have only the `readme` branch
$ git branch
* readme

# But the other branches are actually "hidden"
$ git branch -a
* readme
remotes/origin/debian
remotes/origin/pristine-tar
remotes/origin/upstream

# So start working on one of them with this
# specific command:
$ git checkout -b debian origin/debian

# And by this moment you have this branch as "non-hidden"
# You can go back and forth as you like
$ git checkout -b readme
$ git checkout -b debian
```

### Notes

1. Remember that the **debian** is _not_ the one you get
   right after cloning this repository!
2. [Workaround.org has a nice article][article] on co-maintaining
a Debian package with Git and `git-buildpackage`.

[home]:    https://sites.google.com/site/doctormike/pacman.html
[package]: https://tracker.debian.org/pkg/pacman4console
[article]: https://workaround.org/debian-git-comaintenance
