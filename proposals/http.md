# http
A CEX language extension proposal. Heavily inspired by golang's `http` library.

## Premise
C and C++ were conceived of in a time prior to the prevalence and promiscuity of the Internet.

This is fine and hasn't stopped the development of external libraries to be developed to satisfy this end.

Unfortunately, they have failed to provide these core features under a unified front, or in a "natural C/C++" way, or both.

We are left with a world in which various up-start post-Internet language projects such as Go and JavaScript have carried better implementation standards and user-attractiveness for basic modernities like HTTP (for reasons which go beyond their own linguistic "eases of use").

This is simply unacceptable.

There is nothing intrinsic about C, and *especially* nothing intrinsic to C++, which force the hand of the standard or external library developers to outright ignore or disfigure what could possibly be an elegant and enjoyable web-extended language features.

## Synopsis
```cpp
#include <cex/http>

namespace http = ::cex::http;

int main(void) {
    auto [res, err] = http::get("http://example.com");

    if(err != nullptr) {
        // Help!
    }

    // Do something with response.
}
```

Is this so hard? Is this so much to ask for?

```cpp
#include <iostream>
#include <tuple>
#include <cstdlib>

#include <cex/http>

namespace http = ::cex::http;

int main(void) {
    std::tie(res, err) = http::get("http://example.com");

    if(err != nullptr) {
        // Help!
        std::cerr << err.Error() << std::endl;
        exit(1);
    }

    // Do something with response.
    std::cout << res.Body() << std::endl;
}
```

For the diehard explicitists: is this also not too much to ask?

## Why Go?
Or Golang-inspired, to be precise.

The question is ill-suited for what it intends to attend to: I could tout that Go's standards are well-grounded and likely incorporates many of Google's pre-existing C++ style-guide resolves to their qualms about poor language etiquette; or, that I myself take a liking to its stylistic impressions. But this misses the point at best.

CEX could have multi-lingual extension implements for all I care; borrowing at once from Python, then JavaScript, then C# before coming around again to a third-party C++ library. Whatever inspires improvement within the CEX philosophy is welcome.

What it does **not** admonish is a poorly-constructed mish-mash of inconsistent noise, which at once tries to impress others with their knowledge of the language on the one hand (yes, C++ developers) while paying disrespects to all who were supposed to *use* and therefore benefit from the work in the first place.

Indeed, it would not be right to cite multiple sources of inspiration as admirable without specifying that drawing from many such inspirations, all at once, in quite a literal fashion, would spell nothing but disaster. In this sense, inspiration from diverse sources is welcome *insofar* as it portrays and maintains homage to the original framework it drew upon.

In other words, it would be far better to have concurrently maintained `cex::py::http` and `cex::go::http` namespace-separated instances of library improvements than any manner of half-Go-half-Python implement under a single `cex::http` name. (Why bother if it's going to suck, anyway?)

So I digress. I hope at least to have elucidated a bit on why, here and now, Go is being sourced for inspiration: for no reason *other* than the fact that this is the current inspiration for this specific extension.

May God have mercy on us.
