python

import sys, os.path
sys.dont_write_bytecode = True

sys.path.insert(0, os.path.expanduser('~/mux/example/python'))
for gcc in ['gcc-9', 'gcc-8', 'gcc-7']:
    sys.path.insert(0, os.path.expanduser('/usr/share/{}/python'.format(gcc)))

try:
    from libstdcxx.v6.printers import register_libstdcxx_printers
    register_libstdcxx_printers(None)
except e:
    print 'GCC printers error: ', e

try:
    import qt5printers
    qt5printers.register_printers(gdb.current_objfile())
except e:
    print 'QT printers error: ', e

end
