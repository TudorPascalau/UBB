USE LaboratorGestiuneJocuri;
GO

Create Table DatabaseVersion
(
    id INT NOT NULL,
    current_version INT NOT NULL,

    CONSTRAINT PK_DatabaseVersion PRIMARY KEY (id),
    CONSTRAINT CK_DatabaseVersion_Id CHECK (id = 1),
    CONSTRAINT CK_DatabaseVersion_CurrentVersion
        CHECK (current_version BETWEEN 0 AND 5)
);
GO

INSERT INTO DatabaseVersion (id, current_version)
VALUES (1, 0);
GO
