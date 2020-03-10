QT +=  widgets multimedia

INCLUDEPATH =   toolkit-qt/include \
                toolkit-signal/include\
                app-music/include

HEADERS = 	toolkit-qt/include/SignalDisplay.h \
			toolkit-qt/include/BufferedSignalDisplay.h \
			toolkit-signal/include/FFT.h \
			toolkit-signal/include/SineGenerator.h \
			app-music/include/workers/Worker.h \
			app-music/include/workers/WorkerFFT.h \
			app-music/include/workers/WorkerMusicPlayer.h \
			app-music/include/workers/WorkerSignalGenerator.h \
			app-music/include/interface/MainWindow.h \
                        app-music/include/application/Application.h
			
			
SOURCES = 	toolkit-qt/src/SignalDisplay.cpp \
			toolkit-qt/src/BufferedSignalDisplay.cpp \
			toolkit-signal/src/FFT.cpp \
			toolkit-signal/src/SineGenerator.cpp \
			app-music/src/workers/Worker.cpp \
			app-music/src/workers/WorkerFFT.cpp \
			app-music/src/workers/WorkerMusicPlayer.cpp \
			app-music/src/workers/WorkerSignalGenerator.cpp \
			app-music/src/interface/MainWindow.cpp \
			app-music/src/application/Application.cpp \
                        app-music/src/application/main.cpp
			
FORMS =		app-music/ui/interface/MainWindow.ui

   
                
