c = run_command([meson.source_root() + '/meson_helpers/grabber.sh'])
sources = c.stdout().strip().split('\n')

clang_format = find_program(['clang-format'], required : false)
if clang_format.found() == true
	run_command(['clang-format','-i','-style=file','-assume-filename=.clang-format',sources])
endif 

boost_dep = [
    cxx.find_library('boost_system'),
    cxx.find_library('boost_filesystem'),
]

yaml_cpp = cxx.find_library('yaml-cpp')
fmt_lib = cxx.find_library('fmt')

poco_dep = [
	cxx.find_library('PocoNet'),
	cxx.find_library('PocoFoundation'),
	cxx.find_library('PocoNetSSL'),
	cxx.find_library('ssl'),
]


iharr_lib = library(
    'iharr', 
    sources,
    include_directories : [global_inc],
    dependencies: [ yaml_cpp, boost_dep, fmt_lib, poco_dep ],
	install : true)
