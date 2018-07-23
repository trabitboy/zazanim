for SRC in `find neoback/ -name "*.bmp" `
do
	echo $SRC
	cp $SRC win32/
done
