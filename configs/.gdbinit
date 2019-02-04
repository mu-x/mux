python

import sys, os.path
sys.dont_write_bytecode = True
sys.path.insert(0, os.path.expanduser('~/mux/example/python'))

import qt5printers
qt5printers.register_printers(gdb.current_objfile())

end
