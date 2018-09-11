c = run_command([meson.source_root() + '/meson_helpers/grabber.sh'])
sources = c.stdout().strip().split('\n')

run_command(['clang-format','-i','-style=file','-assume-filename=.clang-format',sources])

boost_dep = [
    cxx.find_library('boost_system'),
    cxx.find_library('boost_filesystem'),
]

yaml_cpp = cxx.find_library('yaml-cpp')
fmt_lib = cxx.find_library('fmt')


iharr_lib = library(
    'iharr', 
    sources,
    #include_directories : inc,
    dependencies: [ yaml_cpp, boost_dep, fmt_lib ],
	install : true)
