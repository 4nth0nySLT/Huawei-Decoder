from distutils.core import setup, Extension
 
module1 = Extension('decoder',
include_dirs = ['./include'],
ources = ['decoder.cpp'])
 
setup (name = 'decoder',
        version = '1.3.4',
        author="Anthony López Tinoco",
        description = 'Decode password Huawei',
        url="https://github.com/4nth0nySLT",
        ext_modules = [module1])