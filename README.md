ClubTenisPadelAdminQt
Club Tennis Padel adminstrator in Qt
In order to use the Qt mysql driver plugin, checkout qtbase, go to src/plugins/sqldrivers/mysql, and run
qmake  "LIBS+=-Ldirectory_with_mysqlclient_library" mysql.pro
make 
make install

This project mantains the club database, used by the ClubTenisPadelServer application
