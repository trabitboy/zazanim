adb uninstall zaza.stable
cd jni/
ndk-build.cmd V=1 NDK_DEBUG=1
cd ..
ant clean debug
adb install bin/zazastable-debug.apk
adb push note4redirect.txt /storage/self/primary/Android/data/zaza.stable/files/redirect.txt
adb shell "mkdir /storage/9C33-6BBD/Android/data/zaza.stable"
adb shell "mkdir /storage/9C33-6BBD/Android/data/zaza.stable/files"

#adb shell monkey -p your.app.package.name -c android.intent.category.LAUNCHER 1

