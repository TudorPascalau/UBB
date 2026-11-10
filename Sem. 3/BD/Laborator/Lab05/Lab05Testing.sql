USE LaboratorGestiuneJocuri;
GO

EXEC goToVersion 1;
GO

SELECT version FROM versionTable;

-- caractesteristicile coloanelor
SELECT TABLE_NAME, COLUMN_NAME, DATA_TYPE,
       CHARACTER_MAXIMUM_LENGTH, IS_NULLABLE, COLUMN_DEFAULT
FROM INFORMATION_SCHEMA.COLUMNS
WHERE (TABLE_NAME = 'Users' AND COLUMN_NAME = 'password_hash')
   OR (TABLE_NAME = 'Games' AND COLUMN_NAME IN ('price', 'system_requirements'));

-- daca exista tabela WishlistItems sau nu
SELECT OBJECT_ID(N'WishlistItems', N'U') AS WishlistItemsId;

-- chei straine definite in WishlistItems sau in Reviews cu referinta la UserGames
SELECT name, OBJECT_NAME(referenced_object_id) AS referenced_table
FROM sys.foreign_keys
WHERE parent_object_id = OBJECT_ID(N'WishlistItems', N'U')
   OR name = N'FK_Reviews_UserGames';

-- cheile primare definite in WishlistItems
SELECT COLUMN_NAME, ORDINAL_POSITION
FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE
WHERE TABLE_NAME = 'WishlistItems'
  AND CONSTRAINT_NAME = 'PK_WishlistItems'
ORDER BY ORDINAL_POSITION;

