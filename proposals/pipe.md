# pipe
A proposal for multi-stage but tightly woven abstract pipelines.

## Premise
The best encapsulation of this idea is what C++ puts forward in its `iostream` piping of data with the `<<` and `>>` operators.

While instead of needing to replace the notion (or indeed, the language implementations themselves) for this to work, I think they could be expanded to consider larger 'assemblies'.

For example, the option to perform an `http::get()` alone is helpful in web-driven applications. But a high-level routing of web-driven requests and processors is something utterly different.

## Example
```cpp
#include <cex/http>
#include <cex/pipe>

int main(void) {
    client <| http::parse <| req;
}
```
