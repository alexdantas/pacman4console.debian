Description: makes Makefile compliant with Debian and adds GCC hardening.
Author: Joao Eriberto Mota Filho <eriberto@eriberto.pro.br>
Last-Update: 2014-08-12
Index: pacman4console/Makefile
===================================================================
--- pacman4console.orig/Makefile
+++ pacman4console/Makefile
@@ -1,30 +1,27 @@
-prefix=/usr/local
-bindir=$(prefix)/bin
-datarootdir=$(prefix)/share
+PREFIX=/usr/local
+BINDIR=$(PREFIX)/bin
+DATAROOTDIR=$(PREFIX)/share
 
 all:
-	gcc pacman.c     -o pacman     -DDATAROOTDIR=\"$(datarootdir)\" $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -lncurses
-	gcc pacmanedit.c -o pacmanedit -DDATAROOTDIR=\"$(datarootdir)\" $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -lncurses
+	gcc pacman.c     -o pacman     -DDATAROOTDIR=\"$(DATAROOTDIR)\" $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -lncurses
+	gcc pacmanedit.c -o pacmanedit -DDATAROOTDIR=\"$(DATAROOTDIR)\" $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -lncurses
 
 install:    all
-	mkdir -p $(DESTDIR)$(bindir)
-	mkdir -p $(DESTDIR)$(datarootdir)/pacman
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
-	rm -f $(DESTDIR)$(bindir)/pacman
-	rm -f $(DESTDIR)$(bindir)/pacmanedit
-	rm -f $(DESTDIR)$(datarootdir)/pacman/Levels/level0[1-9].dat
-	rm -f $(DESTDIR)$(datarootdir)/pacman/Levels/README
-	rm -f $(DESTDIR)$(datarootdir)/pacman/Levels/template.dat
-	if [ -e $(DESTDIR)$(datarootdir)/pacman/Levels/ ] ; then rmdir $(DESTDIR)$(datarootdir)/pacman/Levels/ ; fi
-	if [ -e $(DESTDIR)$(datarootdir)/pacman/ ] ; then rmdir $(DESTDIR)$(datarootdir)/pacman/ ; fi
+	rm -f $(DESTDIR)$(BINDIR)/pacman
+	rm -f $(DESTDIR)$(BINDIR)/pacmanedit
+	rm -f $(DESTDIR)$(DATAROOTDIR)/pacman/Levels/level0[1-9].dat
+	rm -f $(DESTDIR)$(DATAROOTDIR)/pacman/Levels/README
+	rm -f $(DESTDIR)$(DATAROOTDIR)/pacman/Levels/template.dat
+	if [ -e $(DESTDIR)$(DATAROOTDIR)/pacman/Levels/ ] ; then rmdir $(DESTDIR)$(DATAROOTDIR)/pacman/Levels/ ; fi
+	if [ -e $(DESTDIR)$(DATAROOTDIR)/pacman/ ] ; then rmdir $(DESTDIR)$(DATAROOTDIR)/pacman/ ; fi
 
-clean:	uninstall
+clean:
 	rm -f pacman
 	rm -f pacmanedit
