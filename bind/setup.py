# Copyright (C) 2009 Adriano Monteiro Marques
#
# Author: Joao Paulo de Souza Medeiros <ignotus21@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

from distutils.core import setup, Extension

matrix_module = Extension('matrix',
                          include_dirs = ['../'],
                          extra_objects = ['../code/matrix.o'],
                          extra_compile_args = ['-Wall', '-ggdb'],
                          sources = ['matrix.c'])

som_module = Extension('som',
                       include_dirs = ['../'],
                       extra_objects = ['../code/som.o',
                                        '../code/clann.o',
                                        '../code/metric.o',
                                        '../code/matrix.o'],
                       extra_compile_args = ['-Wall', '-ggdb'],
                       sources = ['som.c'])

metric_module = Extension('metric',
                          include_dirs = ['../'],
                          extra_objects = ['../code/metric.o',
                                           '../code/matrix.o'],
                          extra_compile_args = ['-Wall', '-ggdb'],
                          sources = ['metric.c'])

setup (name = 'clann',
       version = '0.1',
       author='Joao Medeiros',
       author_email='joaomedeiros@dca.ufrn.br',
       description = 'This is the CLANN package',
       ext_modules = [matrix_module,
                      som_module,
                      metric_module])
