qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Widgets', 'Network', 'WebEngineWidgets'])
inc_qt5 = include_directories('/usr/include/qt5/')

# For debian-based
inc_qt5_debian = include_directories('/usr/include/x86_64-linux-gnu/qt5')

moc_files = qt5.preprocess(moc_headers : ['widgets/mainwindow.h', 'widgets/configuration.h', 'widgets/newchannel.h'],
                           ui_files: ['widgets/mainwindow.ui', 'widgets/configuration.ui', 'widgets/newchannel.ui'],
                           include_directories: [inc, inc_qt5_debian])

c = run_command([meson.source_root() + '/meson_helpers/grabber.sh'])
sources = c.stdout().strip().split('\n')

clang_format = find_program(['clang-format'], required : false)
if clang_format.found() == true
	run_command(['clang-format','-i','-style=file','-assume-filename=.clang-format',sources])
endif 

yaml_cpp = cxx.find_library('yaml-cpp')
fmt_lib = cxx.find_library('fmt')

poco_dep = [
	cxx.find_library('PocoNet'),
	cxx.find_library('PocoFoundation'),
	cxx.find_library('PocoNetSSL'),
	cxx.find_library('ssl'),
]


#translations = qt5.compile_translations(ts_files : 'myTranslation_fr.ts', build_by_default : true)
executable('iharr_qt', sources, moc_files,
            include_directories : [inc, global_inc],
            link_with: iharr_lib,
            dependencies : [qt5_dep, yaml_cpp, fmt_lib, poco_dep])

