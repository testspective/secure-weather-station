# Commit Message Convention

This project follows the **Conventional Commits** style.

## Format

```
<type>[optional scope]: <short description>

[optional body]

[optional footer]
```

## Types

| Type       | Use for                                                        |
|------------|-----------------------------------------------------------------|
| `feat`     | A new feature                                                   |
| `fix`      | A bug fix                                                        |
| `docs`     | Documentation changes only                                       |
| `style`    | Formatting changes (whitespace, semicolons, etc.), no logic change |
| `refactor` | Code change that neither fixes a bug nor adds a feature          |
| `perf`     | A change that improves performance                               |
| `test`     | Adding or correcting tests                                        |
| `build`    | Changes to build system or dependencies (npm, cmake, etc.)        |
| `ci`       | Changes to CI/CD configuration                                    |
| `chore`    | Routine tasks, maintenance, no production code change             |

## Scope (optional)

Add in parentheses to indicate which part of the project is affected:

```
feat(auth): add refresh token support
fix(parser): handle empty files correctly
```

## Examples

```
feat: add Google login support
fix: fix memory leak in rendering module
docs: update README with install instructions
refactor: extract validation logic into separate function
test: add unit tests for the config loader
chore: bump dependency versions
```

## Breaking changes

Mark with `!` after the type/scope, or add a `BREAKING CHANGE:` section in the body:

```
feat!: change API response format

BREAKING CHANGE: `id` field is now a string instead of a number
```

## Scopes for hardware/firmware projects

For mixed hardware + firmware projects (e.g. a device with a KiCad schematic/PCB and embedded code), it helps to add a scope that indicates which layer of the project changed:

```
feat(hardware)   – new schematic/PCB elements, new modules or boards
fix(hardware)    – fixes to the electronic design (wrong values, wrong connections, footprint issues)
feat(firmware)   – new functionality in the microcontroller code
fix(firmware)    – bug fixes in firmware code
docs(hardware)   – hardware documentation, schematic exports, rendered images/diagrams
docs(firmware)   – firmware documentation (comments, usage notes, API docs)
chore(hardware)  – KiCad library/footprint/symbol updates, non-functional housekeeping
chore(firmware)  – dependency bumps, toolchain/config housekeeping
```

### Adding a schematic (KiCad files)

- A **new** schematic (new board, new module, first version of a circuit) → `feat(hardware)`
- A **fix** to an existing schematic (corrected component value, fixed wiring) → `fix(hardware)`
- If you commit the KiCad source file (`.kicad_sch`) together with its exported PNG as one unit, treat it as a single change:

  ```
  feat(hardware): add KiCad schematic for sensor board (+ rendered PNG)
  ```

- If the PNG is added separately, purely for documentation purposes (e.g. so the schematic can be previewed without opening KiCad), use a separate commit:

  ```
  docs(hardware): add schematic preview image
  ```

## Rules of thumb

- Use the **imperative mood**: "add feature", not "added feature" or "adds feature".
- Keep the short description under ~50-72 characters.
- Don't capitalize the first letter of the description, and don't end it with a period.
- One logical change per commit.