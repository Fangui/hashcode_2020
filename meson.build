project('hashcode', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

inc = include_directories('gen', 'test_2019/')

openmp = dependency('openmp')

executable('main',
           'test_2019/main.cc',
           c_args: '-fopenmp',
           dependencies : openmp,
           include_directories: inc)
