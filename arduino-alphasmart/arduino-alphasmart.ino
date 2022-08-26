// Inspiration: AlphaSmart Neo
// Implementation Techniques: https://www.finseth.com/craft/#c6
/*****************************************************************
  0   1   2   3   4   5   6   7   8                       9  10  11  <-- text location
  | M | i | n | n | e | a | p | o |   |   |   |   |   | l | i | s |
  -----------------------------------------------------------------
  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  <-- buffer location
  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45     <-- storage location
                P              GS                  GE                <-- references {P: point, GS: gap start, GE: gap end}
*****************************************************************/
