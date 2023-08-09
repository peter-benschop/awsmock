db.createUser(
    {
        user: "admin",
        pwd: "admin",
        roles: [
            { role: "dbOwner", db: "awsmock" },
            { role: "dbOwner", db: "test" }
        ]
    })