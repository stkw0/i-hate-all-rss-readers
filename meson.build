project(
    'iharr',
    'cpp',
    version : '0.0.1',
    license : 'Unlicense',
    default_options : ['cpp_std=c++17']) 

add_global_arguments(['-Wall', '-Wextra'], language : 'cpp')
add_global_arguments(['-DSPDLOG_NO_DATETIME', '-DSPDLOG_NO_THREAD_ID', '-DSPDLOG_FMT_EXTERNAL'], language : 'cpp')

global_inc = include_directories('src/')

cxx = meson.get_compiler('cpp')

subdir('src/lib')
subdir('src/server')
subdir('src/qt_client/iharr')
subdir('src/tests')
