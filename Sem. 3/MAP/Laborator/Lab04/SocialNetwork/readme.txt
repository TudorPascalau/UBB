Configuration
=============
ConfigLoader reads src/main/resources/config.properties through
Properties.load(Reader), using FileReader in try-with-resources. No InputStream
or Stream API is used. repository.type accepts MEMORY, FILE or DATABASE.
Missing or blank properties required by the selected backend, and unknown types,
stop startup with a clear message. File paths are relative to the working
directory; start the application from SocialNetwork.
DATABASE creates repository skeletons without opening a JDBC connection. At the
first read, the application reports that DATABASE persistence is not implemented.

Abstract Factory and OCP
========================
RepositoryFactory defines the creation of a family of user and friendship
repositories. MemoryRepositoryFactory, FileRepositoryFactory and
DbRepositoryFactory each create the corresponding persistence family.
Main uses the factory to create repositories and assemble the service.
The UI receives only SocialNetworkService.
Factory methods receive validators as parameters. Main creates the validators
and passes the same instances to repositories and the service. ConfigLoader
selects the persistence configuration without creating validators.
The database classes implement Repository directly, without a shared base class;
all their repository operations throw UnsupportedOperationException.

A Simple Factory using a switch would require changes to its creation methods
for each new persistence backend. Its advantages are simplicity and fewer classes.
Abstract Factory allows a new factory to be added without changing existing
factories, supporting OCP at the cost of more classes.

Family selection is centralized in ConfigLoader. Adding a backend requires a new
factory, an update to its configuration switch and a new RepositoryType value.
This design does not eliminate every change when extending persistence, but keeps
existing factories, the UI and the service unchanged.
No Singleton is used: the factory instance is created once at startup.

Loading and validation policy
=============================
File repositories receive their path and validator in the constructor. Blank
lines are ignored. A missing data file represents an empty repository; the first
successful save creates the file and any missing parent directories.

Loading stops at the first malformed, invalid or duplicate record. The error
message includes the file name, physical line number and reason, and the original
exception is retained as the cause. A failed load restores the previous state.
We stop loading rather than skip invalid records to avoid starting the application
with an incomplete or inconsistent social network. The reported location allows
the input to be corrected before restarting. The service also validates loaded
entities and verifies that both participants of every friendship exist.

Exception handling
==================
ValidationException, RepositoryException and ServiceException are unchecked.
RepositoryException wraps persistence failures through its (String, Throwable)
constructor. This retains IOException, NumberFormatException (caught through
IllegalArgumentException), DateTimeParseException or ValidationException as the
original cause of a load failure. I/O failures during writing retain their cause
as well. Missing configuration files are startup errors, unlike missing data files.

Repository and service catch blocks perform exception translation or recovery;
they do not display user messages. File writes use a temporary file followed by
atomic replacement. Failed writes restore the previous in-memory state. If
temporary-file cleanup fails, that error is suppressed on the original I/O cause.
Removing a user also removes incident friendships. On persistence failure, the
service attempts to restore removed friendships and rethrows the original error.
An incomplete recovery produces an explicit message, retains the original failure
as its cause and preserves recovery failures as suppressed exceptions.

The UI reports invalid numeric input, invalid arguments, validation errors,
invalid network operations and persistence failures, then continues the menu.
Closed input during an operation is reported and ends the UI cleanly.
Main reports initialization failures because the UI cannot be constructed until
repositories and the service are ready; it then stops startup in a controlled way.
No empty catch blocks, generic catch(Exception)/catch(Throwable), or
printStackTrace-only handling are used.

Public exception contracts are documented in Javadoc. Overridden methods inherit
their interface or superclass contracts; constructors document their own argument
and loading failures. Factory contracts describe backend-specific failures,
including null-validator checks and failures when loading file repositories.
