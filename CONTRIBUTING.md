# Contributing

We welcome all contributions to this repository.

However, please note that this work is related with the evaluation process of
an university course as also we expect some general standards from the
contributors explained below.

Because of that, we suggest that the easy way to make your contribution
accepted is first discuss the change you wish to make via issue, email, or any
other method with the owners of this repository before making a change.

To finish, please note that we have a code of conduct, make sure you
understand and follow it in all your interactions with the project.

## Contributor Code of Conduct

As contributors and maintainers of this project, and in the interest of
fostering an open and welcoming community, we pledge to respect all people who
contribute through reporting issues, posting feature requests, updating
documentation, submitting pull requests or patches, and other activities.

We are committed to making participation in this project a harassment-free
experience for everyone, regardless of level of experience, gender, gender
identity and expression, sexual orientation, disability, personal appearance,
body size, race, ethnicity, age, religion, or nationality.

Examples of unacceptable behavior by participants include:

* The use of sexualized language or imagery
* Personal attacks
* Trolling or insulting/derogatory comments
* Public or private harassment
* Publishing other's private information, such as physical or electronic
	addresses, without explicit permission.
* Other unethical or unprofessional conduct.

Project maintainers have the right and responsibility to remove, edit, or
reject comments, commits, code, wiki edits, issues, and other contributions
that are not aligned to this Code of Conduct.

By adopting this Code of Conduct, project maintainers commit themselves to
fairly and consistently applying these principles to every aspect of managing
this project. Project maintainers who do not follow or enforce the Code of
Conduct may be permanently removed from the project team.

This code of conduct applies both within project spaces and in public spaces
when an individual is representing the project or its community.

Instances of abusive, harassing, or otherwise unacceptable behavior may be
reported by opening an issue or contacting one or more of the project maintainers.

This Code of Conduct is adapted from the
[Contributor Covenant](http://contributor-covenant.org), version 1.4.0,
available at
[http://contributor-covenant.org/version/1/4/](http://contributor-covenant.org/version/1/4/)


## Documentation

We expect a minimum level of documentation on all your work. Also, we expect
you to provide in all source files you produce a brief description,
the author name and information, date, knowns bugs and copyright info.

Although not necessarily obligatory, we STRONGLY recommend that you follow
doxygen commenting code style ([doxygen](http://www.stack.nl/~dimitri/doxygen/))
 in order to allow future auto documenting scripts to parse and document the
entirely project.

One brief example of documentation in this style is:

```
/** @file 	calc.s
 *	@brief	Simple assembly calculator
 *	
 *	Very basic calculator in assembly.
 *	It performs x + y, x - y, x * y, x / y.
 *	Opcodes for the operations:
 *		- 0 for sum
 *		- 1 for sub
 *		- 2 for mul
 *		- 3 for div
 *
 *	@author		Decio Lauro Soares (deciolauro@gmail.com)
 *	@date		2016
 *	@bug		Negative remainder in some divisions
 *	@warning	Overflow and division by zero not treated
 * 	@copyright	GNU Public License v3
 */

```

## Pull Request Process

1. Make sure your code follow the Documentation standards.
2. Make sure your pull request address only ONE feature/problem/bug 
	(if necessary open many pull requests)
3. Make sure your code build (and pass any existing tests) before submitting
	a pull request
4. If appropriated, update the README.md with details of your changes.
5. Don't forget to include the version numbers to the new version that this
	Pull Request would represent. The versioning scheme we use is
	[SemVer](http://semver.org/) and a brief summary to it can be found on the
	specific topic of the current [README](README.md).
6. When in doubt, feel free to firstly create a new issue asking the question.
