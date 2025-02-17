// ********************************
// * BON COLOR REGISTRATION FUNCS * (255 MAX ACCEPTED)
// ********************************
// ........................................................
void bon_reg_color(int _red, int _green, int _blue){
    if(bon_max_creg < 255){                         // TEST IF A COLOR MAY BE PUSHED
        bon_colors[0][bon_max_creg] =   _red;       // SET RED COLOR IN STACK
        bon_colors[1][bon_max_creg] = _green;       // SET GREEN COLOR IN STACK
        bon_colors[2][bon_max_creg] =  _blue;       // SET BLUE COLOR IN STACK
        bon_max_creg++;                             // MOVE POINTER
    }
}
// ---------------------------------------------------
void bon_create_colormatic () {
    bon_reg_color(255,255,255); // 0
    bon_reg_color(255,  0,  0); // 1 
    bon_reg_color(  0,255,  0); // 2
    bon_reg_color(  0,  0,255); // 3
    bon_reg_color(255,  0,255); // 4
    bon_reg_color(  0,255,255); // 5
    bon_reg_color(255,255,  0); // 6
}