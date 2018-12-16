inc = include_directories('networking')

c = run_command([meson.source_root() + '/meson_helpers/grabber.sh'])
sources = c.stdout().strip().split('\n')

clang_format = find_program(['clang-format'], required : false)
if clang_format.found() == true
	run_command(['clang-format','-i','-style=file','-assume-filename=.clang-format',sources])
endif 

boost_dep = [
    cxx.find_library('boost_system'),
]

sql_dep = [cxx.find_library('sqlite3')]

thread_dep = dependency('threads')

jwt_dep = [
	cxx.find_library('jwt'),
	cxx.find_library('crypto'),
	cxx.find_library('ssl'),
]

poco_dep = [
	cxx.find_library('PocoNet'),
	cxx.find_library('PocoFoundation'),
	cxx.find_library('PocoNetSSL'),
	cxx.find_library('ssl'),
]

fmt_lib = cxx.find_library('fmt')

yaml_cpp = cxx.find_library('yaml-cpp')


iharrn = executable(
    'iharr', 
    sources,
    include_directories : [inc, global_inc],
    dependencies: [ boost_dep, sql_dep, thread_dep, jwt_dep, fmt_lib, poco_dep, yaml_cpp],
    link_with: [iharr_lib],
	install : true)

