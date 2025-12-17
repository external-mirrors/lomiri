# Lomiri

Lomiri is the operating environment for everywhere. It is able to span the gaps between touch, mouse, and keyboard; between phones, tablets, and workstations; and look good doing it.

This repository contains the new version of Lomiri which powers Ubuntu Touch and serves as the upstream for packaging Lomiri outside of Ubuntu Touch.

Unity8 has been renamed to Lomiri in Ubuntu Touch based on Ubuntu 20.04 and higher.

## Developing Lomiri on Ubuntu Touch

Lomiri can be built and its test suite run using [`clickable`](https://clickable-ut.dev). This is a convenient method to try out most graphical changes to Lomiri without an annoying redeployment process. If you wish to test your changes on your device or make changes that are more difficult to test without real hardware, check out [Making changes and testing locally on the UBports documentation](https://docs.ubports.com/en/latest/systemdev/testing-locally.html). If not, read on.

Before you start, [install Clickable](https://clickable-ut.dev/en/latest/install.html).

Now, clone this repository to your computer: `git clone https://gitlab.com/ubports/development/core/lomiri.git`

Move into this directory: `cd lomiri`

Now you can use the full suite of tools provided by this repository's [clickable.yaml](clickable.yaml). For example:

* `clickable ide qtcreator` will open QtCreator with this repository open as a project. You can edit and build the project this way, but running the tests will be a bit difficult.
* `clickable build --debug` will build Lomiri in the same environment as it would receive in Ubuntu Touch.
* `clickable test` will run the entire Lomiri test suite. This test suite includes graphical tests (which are run on a virtual, invisible desktop) and non-graphical unit tests. These tests make sure Lomiri functions as prescribed and prevents new bugs from being added. You should run them before you create a PR on this repository. This command takes about 7 minutes on an Intel i7-8550U, so plan your time accordingly and use the next two options to reduce the number of times you need to run the whole test suite...
* `clickable ide 'cd build/x86_64-linux-gnu/lomiri/ && make tryShell'` and similar commands that replace the `Shell` with another test target defined in [tests/qmltests/CMakeLists.txt](tests/qmltests/CMakeLists.txt) allow trying out some Lomiri components in a mock environment. You can use this to try out your changes to Lomiri as you develop.
* `clickable ide 'cd build/x86_64-linux-gnu/lomiri/ && make xvfbtestShell'` and similar commands that replace the `Shell` with another test target defined in [tests/qmltests/CMakeLists.txt](tests/qmltests/CMakeLists.txt) allow running a single TestCase. You can remove the `xvfb` part of the make target to run the test case graphically, which might help you see what is causing the test to fail.


For testing as a debian package locally, see https://docs.ubports.com/en/latest/systemdev/testing-locally.html

## i18n: Translating Lomiri into your Language

You can easily contribute to the localization of this project (i.e. the
translation into your language) by visiting (and signing up with) the
Hosted Weblate service:
https://hosted.weblate.org/projects/lomiri/lomiri

The localization platform of this project is sponsored by Hosted Weblate
via their free hosting plan for Libre and Open Source Projects.
