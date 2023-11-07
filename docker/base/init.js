
db = connect('mongodb://localhost/admin');

db.createUser({
    user: "admin",
    pwd: "admin",
    roles: [
        { role: "userAdminAnyDatabase", db: "admin" },
        { role: "readWriteAnyDatabase", db: "admin" },
        { role: "dbAdminAnyDatabase",   db: "admin" },
        { role: "userAdmin", db: "awsmock" },
        { role: "dbAdmin",   db: "awsmock" },
        { role: "readWrite", db: "awsmock" }
    ]
});
