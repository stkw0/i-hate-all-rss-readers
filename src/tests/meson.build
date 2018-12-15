c = run_command([meson.source_root() + '/meson_helpers/grabber.sh'])
sources = c.stdout().strip().split('\n')

sql_dep = [
    cxx.find_library('sqlpp11-connector-sqlite3'),
    cxx.find_library('sqlite3')
]

iharrn = executable('unit_tests', 
	sources, 
	include_directories : [global_inc],
	dependencies: [sql_dep],
	)
