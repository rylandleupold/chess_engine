### Building
Run `cmake .\build\`

Hit `F7`

`Ctrl+Shift+P` -> Cmake: Build

### Running
Run `.\build\Debug\ChessEngine.exe`

Hit `F5`

Click play icon in the "Run and Debug" menu
         
### Testing
Run `.\build\tests\Debug\ChessEngineTests.exe`


TODO: 
    - Replace lsb() -> clearLsb() operations with new popLsb() method
    - Pull out common knight, bishop, rook, queen populateXMoves code into helper function (be wary of if statements)

Unsure/Untested Code:
    - populatePinnedPieceMoves() and its potential impact on regular move generator functions via pinned Bitboard