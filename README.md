# otto-tui
create text apps and games easily
# simple usage:
```
#include "otto-tui.h"                  // import the library

int main(){
    Canvas canvas = new_canvas();      // Canvas structure (this is what you draw graphics to)
    Ezi ezi = new_ezi();               // EZ-Input structure or "Ezi"
    int run = 1;                       // flag to determine when to stop
    while(run){                        // loop until stopped
        printf("\033[2J");             // clear the screen
        render_canvas(&canvas);        // render the canvas
        get_keypress_ezi(&ezi);        // wait for key input
        if(ezi.key == "escape"){       // check if key is the escape key
            run = 0;                   // kill the loop
        }
    }
    destroy_ezi();                     // free the ezi for fun
}
```
# Glyph
## Struct
- `char ch`
- `bool invert`
## Functions
### new_glyph
- return-type: `Glyph`
- parameters:
    - `char ch`
    - `bool invert`
- usage: `Glyph my_glyph = new_glyph('A', false)`
# Canvas
## Struct
- `Glyph glyphs[500][500]`
- `int w`
- `int h`
## Functions
### new_canvas
- return-type: `Canvas`
- parameters: 
    - NONE
- usage: `Canvas my_canvas = new_canvas()`
### print_char_canvas
- return-type: `void`
- parameters: 
    - `Canvas* canvas` 
    - `char ch` 
    - `bool invert` 
    - `int x` 
    - `int y`
### print_string_canvas
- return-type: `void`
- parameters: 
    - `Canvas* canvas`
    - `char* string`
    - `bool invert`
    - `int x`
    - `int y`
### fill_line_canvas
- return-type: `void`
- parameters: 
    - `Canvas* canvas`
    - `char ch`
    - `bool invert`
    - `int line`
### fill_canvas
- return-type: `void`
- parameters: 
    - `Canvas* canvas`
    - `char ch`
    - `bool invert`
### render_canvas
- return-type: `void`
- parameters: 
    - `Canvas* canvas`
