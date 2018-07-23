for SRC in `find win32/ -name "*.bmp" `
do
	echo $SRC
	adb push $SRC /mnt/sdcard/Android/data/zaza.dev/files/
done

for SRC in `find win32/ -name "*.wav" `
do
        echo $SRC
        adb push $SRC /mnt/sdcard/Android/data/zaza.dev/files/
done

#adb push neoback/* /mnt/sdcard/Android/data/org.libsdl.app/files/
#adb push frame000.bmp /mnt/sdcard/Android/data/org.libsdl.app/files/
