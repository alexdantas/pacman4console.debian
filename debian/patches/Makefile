Description: makes Makefile compliant with Debian and adds GCC hardening.
Author: Joao Eriberto Mota Filho <eriberto@eriberto.pro.br>
Last-Update: 2014-02-12
--- pacman4console.orig/Makefile
+++ pacman4console/Makefile
@@ -9,12 +9,11 @@ all:
 install:    all
 	mkdir -p $(DESTDIR)$(bindir)
 	mkdir -p $(DESTDIR)$(datarootdir)/pacman
-	cp -fR Levels/ $(DESTDIR)$(datarootdir)/pacman/
-	-chown root:games $(DESTDIR)$(bindir)/pacman
-	-chown root:games $(DESTDIR)$(datarootdir)/pacman -R
-	chmod 750 $(DESTDIR)$(bindir)/pacman
-	chmod 750 $(DESTDIR)$(bindir)/pacmanedit
-	chmod 750 $(DESTDIR)$(datarootdir)/pacman/ -R
+	install -D pacman $(DESTDIR)/usr/games/pacman4console
+	install -D pacmanedit $(DESTDIR)/usr/bin/pacman4consoleedit
+	install -d $(DESTDIR)/usr/share/pacman4console/Levels
+	install -m 644 Levels/*dat $(DESTDIR)/usr/share/pacman4console/Levels/
+
 
 uninstall:
 	rm -f $(DESTDIR)$(bindir)/pacman
