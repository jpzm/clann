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

"""
"""

import clann.matrix

class Matrix(object):
    """
    """
    def __init__(self, rows=0, cols=0, fill=0):
        """
        """
        self.matrix = clann.matrix.new(rows, cols)
        clann.matrix.fill(self.matrix, fill)

    def __nonzero__(self):
        """
        """
        return clann.matrix.isnull(self.matrix)

    def __len__(self):
        """
        """
        return sum(clann.matrix.size(self.matrix))

    def __getitem__(self, key):
        """
        """
        if len(key) != 2:
            raise IndexError, "invalid index size"

        i, j = key
        return clann.matrix.get(self.matrix, i, j)

    def __setitem__(self, key, value):
        """
        """
        if len(key) != 2:
            raise IndexError, "invalid index size"

        i, j = key
        return clann.matrix.set(self.matrix, i, j, value)

    def __add__(self, m):
        """
        """
        n = Matrix()
        n.matrix = clann.matrix.add(self.matrix, m.matrix)
        
        return n

    def __sub__(self, m):
        """
        """
        n = Matrix()
        n.matrix = clann.matrix.subtract(self.matrix, m.matrix)
        
        return n

    def __mul__(self, m):
        """
        """
        n = Matrix()
        n.matrix = clann.matrix.product(self.matrix, m.matrix)
        
        return n
