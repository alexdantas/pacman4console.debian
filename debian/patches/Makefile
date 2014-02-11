Description: makes Makefile compliant with Debian and adds GCC hardening.
Author: Joao Eriberto Mota Filho <eriberto@eriberto.pro.br>
Last-Update: 20130506
--- a/Makefile
+++ b/Makefile
@@ -1,17 +1,13 @@
 all:
-	gcc -lncurses pacman.c     -o pacman
-	gcc -lncurses pacmanedit.c -o pacmanedit
+	gcc pacman.c     -o pacman     $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -lncurses
+	gcc pacmanedit.c -o pacmanedit $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -lncurses
 
 install:	all
-	cp pacman /usr/local/bin
-	cp pacmanedit /usr/local/bin
-	mkdir -p /usr/local/share/pacman
-	cp -fR Levels/ /usr/local/share/pacman/
-	chown root:games /usr/local/bin/pacman
-	chown root:games /usr/local/share/pacman -R
-	chmod 750 /usr/local/bin/pacman
-	chmod 750 /usr/local/bin/pacmanedit
-	chmod 750 /usr/local/share/pacman/ -R
+	install -D pacman $(DESTDIR)/usr/games/pacman4console
+	install -D pacmanedit $(DESTDIR)/usr/bin/pacman4consoleedit
+	install -d $(DESTDIR)/usr/share/pacman4console/Levels
+	install -m 644 Levels/*dat $(DESTDIR)/usr/share/pacman4console/Levels/
+	install -D -m 644 Levels/README $(DESTDIR)/usr/share/doc/pacman4console/README.editor
 
 uninstall:
 	rm -f /usr/local/bin/pacman
