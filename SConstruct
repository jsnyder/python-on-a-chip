#
# This file defines how to build PyMite using Scons (www.scons.org)
# Usage:
#   scons tags
#   scons docs
#   scons PLATFORM=<platform>
#


import os, string


supported_platforms = Glob("src/platform/*")
allowed_platforms = [os.path.split(x)[1] for x in map(str, supported_platforms)]


vars = Variables()


# BUILD TARGETS
if "tags" in COMMAND_LINE_TARGETS or "TAGS" in COMMAND_LINE_TARGETS:
    vmfiles = Glob("src/vm/*")
    ctags = Command('tags', vmfiles, "/opt/local/bin/ctags -R *")
    cscope = Command('cscope.out', vmfiles, "cscope -b -c -R")
    pyc_tools = Command('src/tools/cscope.out', Glob("src/tools/*.py"),
                        "src/tools/pycscope.py -f $TARGET $SOURCE")
    pyc_lib = Command('src/lib/cscope.out', Glob("src/lib/*.py"),
                      "src/tools/pycscope.py -f $TARGET $SOURCE")
    tags = Alias('tags', [ctags, cscope, pyc_tools, pyc_lib])
    Alias('TAGS', tags)


# Not yet working
#elif "check" in COMMAND_LINE_TARGETS or "test" in COMMAND_LINE_TARGETS:
#    test = SConscript(["src/tests/unit/SConscript", "src/tests/system/SConscript"])


elif "docs" in COMMAND_LINE_TARGETS or "html" in COMMAND_LINE_TARGETS:
    srcpath = os.path.join("docs", "src")
    rstfiles = Glob(os.path.join(srcpath, "*.txt"))
    htmlpath = os.path.join("docs", "html")
    Mkdir(htmlpath)
    htmlfiles = [string.replace(string.replace(str(s), ".txt", ".html", 1), srcpath, htmlpath, 1)
                 for s in rstfiles]
    html = [Command(htmlfiles[i], rstfiles[i], "rst2html.py $SOURCE $TARGET")
            for i in range(len(rstfiles))]
    htmlalias = Alias("html", html)
    Alias("docs", htmlalias)


elif "dist" in COMMAND_LINE_TARGETS:
    assert "PM_RELEASE" in vars.args.keys(), "Must define PM_RELEASE=RR"
    dist = Command("pymite-%s.tar.gz" % vars.args["PM_RELEASE"], None,
                   "src/tools/pmDist.py %s" % vars.args["PM_RELEASE"])
    AlwaysBuild(dist)
    Alias("dist", dist)


# Default: build a platform; desktop by default
else:
    if len(vars.args) == 0:
        vars.args["PLATFORM"] = "desktop"
    else:
        if vars.args["PLATFORM"] not in allowed_platforms:
            print "Error: must define PLATFORM=<plat> where <plat> is from %s" \
                % str(allowed_platforms)
            Exit(1)
    platform_path = "src/platform/%s/SConscript" % vars.args["PLATFORM"]
    SConscript([platform_path], "vars")
