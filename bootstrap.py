#!/usr/bin/python

import ninja_syntax
import itertools
import os
import fnmatch
import re
import sys
import argparse

# Gets all files from the root that match a specific
# regex pattern.
def get_files(root, pattern):
    pattern = fnmatch.translate(pattern)
    for dir, dirs, files in os.walk(root):
        for f in files:
            if re.match(pattern, f):
                yield os.path.join(dir, f)

# Generates the location in which to store the corresponding
# object file, for a .cpp source file.
def object_file(cpp):
    return os.path.join('obj', re.sub(r'\.cpp', '.o', cpp))

# Argument parsing
parser = argparse.ArgumentParser()
parser.add_argument('--cxx', default='clang++', metavar='executable', help='compiler name')
parser.add_argument('--install-path', default='/usr/local/', metavar='path', help='install path')
args = parser.parse_args()

# Ninja instance
ninja = ninja_syntax.Writer(open('build.ninja', 'w'))

# Ninja variables
ninja.variable('ninja_required_version', '1.5')
ninja.variable('builddir', 'obj')
ninja.variable('include_flags', '-Iinclude -Ideps/catch/include')
ninja.variable('compiler_flags', '-Wall -Wextra -Wno-missing-braces -O2 -Wfatal-errors -Werror -std=c++14')
ninja.variable('linker_flags', '')
ninja.variable('compiler', args.cxx)
ninja.variable('install_path', args.install_path)

# Compilation rule
ninja.rule('cxx',
        command = '$compiler -c $compiler_flags $include_flags $in -o $out',
        description = 'Compiling $in')

# Linking rule
ninja.rule('link',
        command = '$compiler $compiler_flags $linker_flags $in -o $out',
        description = 'Linking $in')

# Installing
ninja.rule('install-headers',
        command = 'cp -vR ./include/ $install_path/include',
        description = 'Installing headers in $in')

# Tests
src_files = list(get_files('test', '*.cpp'))
obj_files = [object_file(cpp) for cpp in src_files]
for cpp in src_files:
    ninja.build(object_file(cpp), 'cxx', inputs = cpp)

ninja.build('tests', 'link', inputs = obj_files)

# Installation
ninja.build('install', 'install-headers')

# Default build
ninja.default('tests')