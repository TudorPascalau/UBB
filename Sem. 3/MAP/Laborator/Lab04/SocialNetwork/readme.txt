Configuration
=============
ConfigLoader reads src/main/resources/config.properties through
Properties.load(Reader), using FileReader in try-with-resources. No InputStream
or Stream API is used. repository.type accepts MEMORY, FILE or DATABASE.
RepositoryFactory validates the loaded properties. Missing or blank properties
required by the selected backend, and unknown types, stop startup with a clear message. File paths are relative to the working
directory; start the application from SocialNetwork.
DATABASE creates repository skeletons without opening a JDBC connection. At the
first read, the application reports that DATABASE persistence is not implemented.

Simple Factory and OCP
======================
RepositoryFactory is a concrete Simple Factory and the only application class
that knows the concrete repository implementations. Its two creation methods use
classic switches and return Repository<Long, User> and
Repository<FriendshipId, Friendship>. Both use the same configured RepositoryType.
The former MemoryRepositoryFactory, FileRepositoryFactory and DbRepositoryFactory
classes have been removed.

ConfigLoader.load reads and returns Properties; it does not select a backend or
create factories. Main passes these properties to new RepositoryFactory(...),
creates validators, and assembles the service using the factory methods.
The UI receives only SocialNetworkService. Main, service and UI do not instantiate
concrete repositories.

The factory copies the properties and validates the type and required parameters
at construction, without opening data files or database connections. Only the
selected backend requires its parameters. File paths and database parameters
remain in configuration, not hardcoded in Java. Factory methods receive the same
validator instances used by the service and create repositories only when called.
Database classes implement Repository directly; their operations still throw
UnsupportedOperationException. Switching to DATABASE requires implementing these
operations and changing configuration, without changing Main, service or UI.

Simple Factory centralizes creation and uses fewer classes than Abstract Factory.
Adding a persistence backend requires a new RepositoryType value, updates to the
creation switches and any backend-specific configuration validation. Consequently,
the factory is not closed to modification under OCP. Abstract Factory, the previous
alternative, allows new concrete factories without modifying existing ones, but
still needs a mechanism to select the configured factory and adds more classes.
The Simple Factory follows the laboratory's main structure and provides the
starting point for replacing both switches with maps of creation functions in
the next laboratory. No functional interfaces or lambdas are introduced here.

SRP separates configuration reading (ConfigLoader) from repository creation
(RepositoryFactory). Service code depends on Repository abstractions (DIP).
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
