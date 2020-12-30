from distutils.core import setup, Extension
 
module1 = Extension('decoder',
include_dirs = ['./include'],

 sources = ['decoder.cpp'])
 
setup (name = 'decoder',
        version = '1.3.3',
        author="Anthony López Tinoco",
        description = 'Decode password Huawei',
        url="https://github.com/4nth0nySLT",
        ext_modules = [module1])