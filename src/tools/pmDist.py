#!/usr/bin/env python

# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2002 Dean Hall
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

"""Creates a release package for PyMite

Makes fresh export (no .svn folders), builds the docs, makes pymite-RR.tar.gz
and creates release tag in the svn repository
"""


import os, string, subprocess, sys, tempfile


REPOS = "https://svn.pymite.python-hosting.com/"


RELEASE_NUM = sys.argv[1]
assert string.atoi(RELEASE_NUM, 16) > 6
print "Building package for release", RELEASE_NUM, "..."
PM_RELEASE = "pymite-%s" % RELEASE_NUM

# Make a fresh export (no .svn folders) in a temporary directory
tempdir = tempfile.gettempdir()
subprocess.check_call(["svn", "export", REPOS + "trunk", PM_RELEASE],
                      cwd = tempdir)

# Build html docs
subprocess.check_call(["make", "html"],
                      cwd = os.path.join(tempdir, PM_RELEASE))

# Make pymite-RR.tar.gz and copy it to the current directory
subprocess.check_call(["tar -cz %s/ > %s.tar.gz" % (PM_RELEASE, PM_RELEASE)],
                      cwd = tempdir, shell=True)
subprocess.check_call(["cp %s.tar.gz ." % os.path.join(tempdir, PM_RELEASE)],
                      shell=True)

# Create release tag in svn repository
subprocess.check_call(["svn",
                       "cp",
                       REPOS + "trunk",
                       REPOS + "tags/%s" % PM_RELEASE,
                       '-m "Tagging PyMite release %s"' % RELEASE_NUM],
                      cwd = tempdir)

print "Done."
