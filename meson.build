project('hashcode', 'cpp',
  version : '0.1',
  default_options : ['warning_level=1', 'cpp_std=c++17'])

inc = include_directories('gen', '2020/')
executable('main',
           '2020/main.cc',
           '2020/heuristic.cc',
           include_directories: inc)
