#include "stdafx.h"
#include "abFont.h"


/*
//
// Font data for 5x7 font
//

// 5x7 font
const uint_8 fiveBySevenCharBitmaps[] =
{
	0b00000000, //         
	0b00000000, //         
	0b01011111, //  # #####
	0b00000000, //         
	0b00000000, //         

	0b00000000, //         
	0b00000111, //      ###
	0b00000000, //         
	0b00000111, //      ###
	0b00000000, //         

	0b00010100, //    # #  
	0b01111111, //  #######
	0b00010100, //    # #  
	0b01111111, //  #######
	0b00010100, //    # #  

	0b00100100, //   #  #  
	0b00101010, //   # # # 
	0b01111111, //  #######
	0b00101010, //   # # # 
	0b00010010, //    #  # 

	0b00100011, //   #   ##
	0b00010011, //    #  ##
	0b00001000, //     #   
	0b01100100, //  ##  #  
	0b01100010, //  ##   # 

	0b00110110, //   ## ## 
	0b01001001, //  #  #  #
	0b01010101, //  # # # #
	0b00100010, //   #   # 
	0b01010000, //  # #    

	0b00000000, //         
	0b00000101, //      # #
	0b00000011, //       ##
	0b00000000, //         
	0b00000000, //         

	0b00000000, //         
	0b00011100, //    ###  
	0b00100010, //   #   # 
	0b01000001, //  #     #
	0b00000000, //         

	0b00000000, //         
	0b01000001, //  #     #
	0b00100010, //   #   # 
	0b00011100, //    ###  
	0b00000000, //         

	0b00001000, //     #   
	0b00101010, //   # # # 
	0b00011100, //    ###  
	0b00101010, //   # # # 
	0b00001000, //     #   

	0b00001000, //     #   
	0b00001000, //     #   
	0b00111110, //   ##### 
	0b00001000, //     #   
	0b00001000, //     #   

	0b00000000, //         
	0b01010000, //  # #    
	0b00110000, //   ##    
	0b00000000, //         
	0b00000000, //         

	0b00001000, //     #   
	0b00001000, //     #   
	0b00001000, //     #   
	0b00001000, //     #   
	0b00001000, //     #   

	0b00000000, //         
	0b01100000, //  ##     
	0b01100000, //  ##     
	0b00000000, //         
	0b00000000, //         

	0b00100000, //   #     
	0b00010000, //    #    
	0b00001000, //     #   
	0b00000100, //      #  
	0b00000010, //       # 

	0b00111110, //   ##### 
	0b01010001, //  # #   #
	0b01001001, //  #  #  #
	0b01000101, //  #   # #
	0b00111110, //   ##### 

	0b00000000, //         
	0b01000010, //  #    # 
	0b01111111, //  #######
	0b01000000, //  #      
	0b00000000, //         

	0b01000010, //  #    # 
	0b01100001, //  ##    #
	0b01010001, //  # #   #
	0b01001001, //  #  #  #
	0b01000110, //  #   ## 

	0b00100001, //   #    #
	0b01000001, //  #     #
	0b01000101, //  #   # #
	0b01001011, //  #  # ##
	0b00110001, //   ##   #

	0b00011000, //    ##   
	0b00010100, //    # #  
	0b00010010, //    #  # 
	0b01111111, //  #######
	0b00010000, //    #    

	0b00100111, //   #  ###
	0b01000101, //  #   # #
	0b01000101, //  #   # #
	0b01000101, //  #   # #
	0b00111001, //   ###  #

	0b00111100, //   ####  
	0b01001010, //  #  # # 
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b00110000, //   ##    

	0b00000001, //        #
	0b01110001, //  ###   #
	0b00001001, //     #  #
	0b00000101, //      # #
	0b00000011, //       ##

	0b00110110, //   ## ## 
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b00110110, //   ## ## 

	0b00000110, //      ## 
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b00101001, //   # #  #
	0b00011110, //    #### 

	0b00000000, //         
	0b00110110, //   ## ## 
	0b00110110, //   ## ## 
	0b00000000, //         
	0b00000000, //         

	0b00000000, //         
	0b01010110, //  # # ## 
	0b00110110, //   ## ## 
	0b00000000, //         
	0b00000000, //         

	0b00000000, //         
	0b00001000, //     #   
	0b00010100, //    # #  
	0b00100010, //   #   # 
	0b01000001, //  #     #

	0b00010100, //    # #  
	0b00010100, //    # #  
	0b00010100, //    # #  
	0b00010100, //    # #  
	0b00010100, //    # #  

	0b01000001, //  #     #
	0b00100010, //   #   # 
	0b00010100, //    # #  
	0b00001000, //     #   
	0b00000000, //         

	0b00000010, //       # 
	0b00000001, //        #
	0b01010001, //  # #   #
	0b00001001, //     #  #
	0b00000110, //      ## 

	0b00110010, //   ##  # 
	0b01001001, //  #  #  #
	0b01111001, //  ####  #
	0b01000001, //  #     #
	0b00111110, //   ##### 

	0b01111110, //  ###### 
	0b00010001, //    #   #
	0b00010001, //    #   #
	0b00010001, //    #   #
	0b01111110, //  ###### 

	0b01111111, //  #######
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b00110110, //   ## ## 

	0b00111110, //   ##### 
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b00100010, //   #   # 

	0b01111111, //  #######
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b00100010, //   #   # 
	0b00011100, //    ###  

	0b01111111, //  #######
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b01000001, //  #     #

	0b01111111, //  #######
	0b00001001, //     #  #
	0b00001001, //     #  #
	0b00000001, //        #
	0b00000001, //        #

	0b00111110, //   ##### 
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b01010001, //  # #   #
	0b00110010, //   ##  # 

	0b01111111, //  #######
	0b00001000, //     #   
	0b00001000, //     #   
	0b00001000, //     #   
	0b01111111, //  #######

	0b00000000, //         
	0b01000001, //  #     #
	0b01111111, //  #######
	0b01000001, //  #     #
	0b00000000, //         

	0b00100000, //   #     
	0b01000000, //  #      
	0b01000001, //  #     #
	0b00111111, //   ######
	0b00000001, //        #

	0b01111111, //  #######
	0b00001000, //     #   
	0b00010100, //    # #  
	0b00100010, //   #   # 
	0b01000001, //  #     #

	0b01111111, //  #######
	0b01000000, //  #      
	0b01000000, //  #      
	0b01000000, //  #      
	0b01000000, //  #      

	0b01111111, //  #######
	0b00000010, //       # 
	0b00000100, //      #  
	0b00000010, //       # 
	0b01111111, //  #######

	0b01111111, //  #######
	0b00000100, //      #  
	0b00001000, //     #   
	0b00010000, //    #    
	0b01111111, //  #######

	0b00111110, //   ##### 
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b01000001, //  #     #
	0b00111110, //   ##### 

	0b01111111, //  #######
	0b00001001, //     #  #
	0b00001001, //     #  #
	0b00001001, //     #  #
	0b00000110, //      ## 

	0b00111110, //   ##### 
	0b01000001, //  #     #
	0b01010001, //  # #   #
	0b00100001, //   #    #
	0b01011110, //  # #### 

	0b01111111, //  #######
	0b00001001, //     #  #
	0b00011001, //    ##  #
	0b00101001, //   # #  #
	0b01000110, //  #   ## 

	0b01000110, //  #   ## 
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b01001001, //  #  #  #
	0b00110001, //   ##   #

	0b00000001, //        #
	0b00000001, //        #
	0b01111111, //  #######
	0b00000001, //        #
	0b00000001, //        #

	0b00111111, //   ######
	0b01000000, //  #      
	0b01000000, //  #      
	0b01000000, //  #      
	0b00111111, //   ######

	0b00011111, //    #####
	0b00100000, //   #     
	0b01000000, //  #      
	0b00100000, //   #     
	0b00011111, //    #####

	0b01111111, //  #######
	0b00100000, //   #     
	0b00011000, //    ##   
	0b00100000, //   #     
	0b01111111, //  #######

	0b01100011, //  ##   ##
	0b00010100, //    # #  
	0b00001000, //     #   
	0b00010100, //    # #  
	0b01100011, //  ##   ##

	0b00000011, //       ##
	0b00000100, //      #  
	0b01111000, //  ####   
	0b00000100, //      #  
	0b00000011, //       ##

	0b01100001, //  ##    #
	0b01010001, //  # #   #
	0b01001001, //  #  #  #
	0b01000101, //  #   # #
	0b01000011, //  #    ##

	0b00000000, //         
	0b00000000, //         
	0b01111111, //  #######
	0b01000001, //  #     #
	0b01000001, //  #     #

	0b00000010, //       # 
	0b00000100, //      #  
	0b00001000, //     #   
	0b00010000, //    #    
	0b00100000, //   #     

	0b01000001, //  #     #
	0b01000001, //  #     #
	0b01111111, //  #######
	0b00000000, //         
	0b00000000, //         

	0b00000100, //      #  
	0b00000010, //       # 
	0b00000001, //        #
	0b00000010, //       # 
	0b00000100, //      #  

	0b01000000, //  #      
	0b01000000, //  #      
	0b01000000, //  #      
	0b01000000, //  #      
	0b01000000, //  #      

	0b00000000, //         
	0b00000001, //        #
	0b00000010, //       # 
	0b00000100, //      #  
	0b00000000, //         

	0b00100000, //   #     
	0b01010100, //  # # #  
	0b01010100, //  # # #  
	0b01010100, //  # # #  
	0b01111000, //  ####   

	0b01111111, //  #######
	0b01001000, //  #  #   
	0b01000100, //  #   #  
	0b01000100, //  #   #  
	0b00111000, //   ###   

	0b00111000, //   ###   
	0b01000100, //  #   #  
	0b01000100, //  #   #  
	0b01000100, //  #   #  
	0b00100000, //   #     

	0b00111000, //   ###   
	0b01000100, //  #   #  
	0b01000100, //  #   #  
	0b01001000, //  #  #   
	0b01111111, //  #######

	0b00111000, //   ###   
	0b01010100, //  # # #  
	0b01010100, //  # # #  
	0b01010100, //  # # #  
	0b00011000, //    ##   

	0b00001000, //     #   
	0b01111110, //  ###### 
	0b00001001, //     #  #
	0b00000001, //        #
	0b00000010, //       # 

	0b00001000, //     #   
	0b00010100, //    # #  
	0b01010100, //  # # #  
	0b01010100, //  # # #  
	0b00111100, //   ####  

	0b01111111, //  #######
	0b00001000, //     #   
	0b00000100, //      #  
	0b00000100, //      #  
	0b01111000, //  ####   

	0b00000000, //         
	0b01000100, //  #   #  
	0b01111101, //  ##### #
	0b01000000, //  #      
	0b00000000, //         

	0b00100000, //   #     
	0b01000000, //  #      
	0b01000100, //  #   #  
	0b00111101, //   #### #
	0b00000000, //         

	0b00000000, //         
	0b01111111, //  #######
	0b00010000, //    #    
	0b00101000, //   # #   
	0b01000100, //  #   #  

	0b00000000, //         
	0b01000001, //  #     #
	0b01111111, //  #######
	0b01000000, //  #      
	0b00000000, //         

	0b01111100, //  #####  
	0b00000100, //      #  
	0b00011000, //    ##   
	0b00000100, //      #  
	0b01111000, //  ####   

	0b01111100, //  #####  
	0b00001000, //     #   
	0b00000100, //      #  
	0b00000100, //      #  
	0b01111000, //  ####   

	0b00111000, //   ###   
	0b01000100, //  #   #  
	0b01000100, //  #   #  
	0b01000100, //  #   #  
	0b00111000, //   ###   

	0b01111100, //  #####  
	0b00010100, //    # #  
	0b00010100, //    # #  
	0b00010100, //    # #  
	0b00001000, //     #   

	0b00001000, //     #   
	0b00010100, //    # #  
	0b00010100, //    # #  
	0b00011000, //    ##   
	0b01111100, //  #####  

	0b01111100, //  #####  
	0b00001000, //     #   
	0b00000100, //      #  
	0b00000100, //      #  
	0b00001000, //     #   

	0b01001000, //  #  #   
	0b01010100, //  # # #  
	0b01010100, //  # # #  
	0b01010100, //  # # #  
	0b00100000, //   #     

	0b00000100, //      #  
	0b00111111, //   ######
	0b01000100, //  #   #  
	0b01000000, //  #      
	0b00100000, //   #     

	0b00111100, //   ####  
	0b01000000, //  #      
	0b01000000, //  #      
	0b00100000, //   #     
	0b01111100, //  #####  

	0b00011100, //    ###  
	0b00100000, //   #     
	0b01000000, //  #      
	0b00100000, //   #     
	0b00011100, //    ###  

	0b00111100, //   ####  
	0b01000000, //  #      
	0b00110000, //   ##    
	0b01000000, //  #      
	0b00111100, //   ####  

	0b01000100, //  #   #  
	0b00101000, //   # #   
	0b00010000, //    #    
	0b00101000, //   # #   
	0b01000100, //  #   #  

	0b00001100, //     ##  
	0b01010000, //  # #    
	0b01010000, //  # #    
	0b01010000, //  # #    
	0b00111100, //   ####  

	0b01000100, //  #   #  
	0b01100100, //  ##  #  
	0b01010100, //  # # #  
	0b01001100, //  #  ##  
	0b01000100, //  #   #  

	0b00000000, //         
	0b00001000, //     #   
	0b00110110, //   ## ## 
	0b01000001, //  #     #
	0b00000000, //         

	0b00000000, //         
	0b00000000, //         
	0b01111111, //  #######
	0b00000000, //         
	0b00000000, //         

	0b00000000, //         
	0b01000001, //  #     #
	0b00110110, //   ## ## 
	0b00001000, //     #   
	0b00000000, //         
};

// Font information for Tahoma 8pt
const FONT_INFO fiveBySevenFontInfo = { 1, '!', 1, NULL, fiveBySevenCharBitmaps };
*/


// 
//  Font data for Microsoft Sans Serif 7pt
// 

// Character bitmaps for Microsoft Sans Serif 7pt
const uint_8 microsoftSansSerif_7ptBitmaps[] =
{
	// @0 '0' (4 pixels wide)
	0x60, //  ## 
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @9 '1' (2 pixels wide)
	0x40, //  #
	0xC0, // ##
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x00, //   
	0x00, //   

	// @18 '2' (4 pixels wide)
	0x60, //  ## 
	0x90, // #  #
	0x10, //    #
	0x20, //   # 
	0x40, //  #  
	0x80, // #   
	0xF0, // ####
	0x00, //     
	0x00, //     

	// @27 '3' (4 pixels wide)
	0x60, //  ## 
	0x90, // #  #
	0x10, //    #
	0x20, //   # 
	0x10, //    #
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @36 '4' (5 pixels wide)
	0x10, //    # 
	0x30, //   ## 
	0x50, //  # # 
	0x90, // #  # 
	0xF8, // #####
	0x10, //    # 
	0x10, //    # 
	0x00, //      
	0x00, //      

	// @45 '5' (4 pixels wide)
	0xF0, // ####
	0x80, // #   
	0xE0, // ### 
	0x10, //    #
	0x10, //    #
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @54 '6' (4 pixels wide)
	0x60, //  ## 
	0x90, // #  #
	0x80, // #   
	0xE0, // ### 
	0x90, // #  #
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @63 '7' (4 pixels wide)
	0xF0, // ####
	0x10, //    #
	0x20, //   # 
	0x20, //   # 
	0x20, //   # 
	0x40, //  #  
	0x40, //  #  
	0x00, //     
	0x00, //     

	// @72 '8' (4 pixels wide)
	0x60, //  ## 
	0x90, // #  #
	0x90, // #  #
	0x60, //  ## 
	0x90, // #  #
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @81 '9' (4 pixels wide)
	0x60, //  ## 
	0x90, // #  #
	0x90, // #  #
	0x70, //  ###
	0x10, //    #
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @90 'A' (7 pixels wide)
	0x10, //    #   
	0x28, //   # #  
	0x28, //   # #  
	0x44, //  #   # 
	0x7C, //  ##### 
	0x82, // #     #
	0x82, // #     #
	0x00, //        
	0x00, //        

	// @99 'B' (4 pixels wide)
	0xE0, // ### 
	0x90, // #  #
	0x90, // #  #
	0xE0, // ### 
	0x90, // #  #
	0x90, // #  #
	0xE0, // ### 
	0x00, //     
	0x00, //     

	// @108 'C' (5 pixels wide)
	0x70, //  ### 
	0x88, // #   #
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      

	// @117 'D' (5 pixels wide)
	0xE0, // ###  
	0x90, // #  # 
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x90, // #  # 
	0xE0, // ###  
	0x00, //      
	0x00, //      

	// @126 'E' (4 pixels wide)
	0xF0, // ####
	0x80, // #   
	0x80, // #   
	0xF0, // ####
	0x80, // #   
	0x80, // #   
	0xF0, // ####
	0x00, //     
	0x00, //     

	// @135 'F' (4 pixels wide)
	0xF0, // ####
	0x80, // #   
	0x80, // #   
	0xF0, // ####
	0x80, // #   
	0x80, // #   
	0x80, // #   
	0x00, //     
	0x00, //     

	// @144 'G' (5 pixels wide)
	0x70, //  ### 
	0x88, // #   #
	0x80, // #    
	0x98, // #  ##
	0x88, // #   #
	0x88, // #   #
	0x78, //  ####
	0x00, //      
	0x00, //      

	// @153 'H' (5 pixels wide)
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0xF8, // #####
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x00, //      
	0x00, //      

	// @162 'I' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x00, //  

	// @171 'J' (4 pixels wide)
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x10, //    #
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @180 'K' (5 pixels wide)
	0x88, // #   #
	0x90, // #  # 
	0xA0, // # #  
	0xC0, // ##   
	0xA0, // # #  
	0x90, // #  # 
	0x88, // #   #
	0x00, //      
	0x00, //      

	// @189 'L' (4 pixels wide)
	0x80, // #   
	0x80, // #   
	0x80, // #   
	0x80, // #   
	0x80, // #   
	0x80, // #   
	0xF0, // ####
	0x00, //     
	0x00, //     

	// @198 'M' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0xC6, // ##   ##
	0xAA, // # # # #
	0xAA, // # # # #
	0x92, // #  #  #
	0x82, // #     #
	0x00, //        
	0x00, //        

	// @207 'N' (5 pixels wide)
	0x88, // #   #
	0xC8, // ##  #
	0xC8, // ##  #
	0xA8, // # # #
	0x98, // #  ##
	0x98, // #  ##
	0x88, // #   #
	0x00, //      
	0x00, //      

	// @216 'O' (5 pixels wide)
	0x70, //  ### 
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      

	// @225 'P' (5 pixels wide)
	0xF0, // #### 
	0x88, // #   #
	0x88, // #   #
	0xF0, // #### 
	0x80, // #    
	0x80, // #    
	0x80, // #    
	0x00, //      
	0x00, //      

	// @234 'Q' (5 pixels wide)
	0x70, //  ### 
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x98, // #  ##
	0x70, //  ### 
	0x08, //     #
	0x00, //      

	// @243 'R' (5 pixels wide)
	0xF0, // #### 
	0x88, // #   #
	0x88, // #   #
	0xF0, // #### 
	0x90, // #  # 
	0x88, // #   #
	0x88, // #   #
	0x00, //      
	0x00, //      

	// @252 'S' (4 pixels wide)
	0x60, //  ## 
	0x90, // #  #
	0x80, // #   
	0x60, //  ## 
	0x10, //    #
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @261 'T' (5 pixels wide)
	0xF8, // #####
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x00, //      
	0x00, //      

	// @270 'U' (5 pixels wide)
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x88, // #   #
	0x70, //  ### 
	0x00, //      
	0x00, //      

	// @279 'V' (7 pixels wide)
	0x82, // #     #
	0x82, // #     #
	0x44, //  #   # 
	0x44, //  #   # 
	0x28, //   # #  
	0x28, //   # #  
	0x10, //    #   
	0x00, //        
	0x00, //        

	// @288 'W' (9 pixels wide)
	0x88, 0x80, // #   #   #
	0x88, 0x80, // #   #   #
	0x55, 0x00, //  # # # # 
	0x55, 0x00, //  # # # # 
	0x22, 0x00, //   #   #  
	0x22, 0x00, //   #   #  
	0x22, 0x00, //   #   #  
	0x00, 0x00, //          
	0x00, 0x00, //          

	// @306 'X' (6 pixels wide)
	0x84, // #    #
	0x48, //  #  # 
	0x30, //   ##  
	0x30, //   ##  
	0x30, //   ##  
	0x48, //  #  # 
	0x84, // #    #
	0x00, //       
	0x00, //       

	// @315 'Y' (5 pixels wide)
	0x88, // #   #
	0x88, // #   #
	0x50, //  # # 
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x20, //   #  
	0x00, //      
	0x00, //      

	// @324 'Z' (4 pixels wide)
	0xF0, // ####
	0x10, //    #
	0x20, //   # 
	0x40, //  #  
	0x40, //  #  
	0x80, // #   
	0xF0, // ####
	0x00, //     
	0x00, //     

	// @333 'a' (4 pixels wide)
	0x00, //     
	0x00, //     
	0xE0, // ### 
	0x10, //    #
	0x70, //  ###
	0x90, // #  #
	0x70, //  ###
	0x00, //     
	0x00, //     

	// @342 'b' (4 pixels wide)
	0x80, // #   
	0x80, // #   
	0xE0, // ### 
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0xE0, // ### 
	0x00, //     
	0x00, //     

	// @351 'c' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x60, //  ## 
	0x90, // #  #
	0x80, // #   
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @360 'd' (4 pixels wide)
	0x10, //    #
	0x10, //    #
	0x70, //  ###
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x70, //  ###
	0x00, //     
	0x00, //     

	// @369 'e' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x60, //  ## 
	0x90, // #  #
	0xF0, // ####
	0x80, // #   
	0x70, //  ###
	0x00, //     
	0x00, //     

	// @378 'f' (2 pixels wide)
	0x40, //  #
	0x80, // # 
	0xC0, // ##
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x00, //   
	0x00, //   

	// @387 'g' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x70, //  ###
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x70, //  ###
	0x10, //    #
	0xE0, // ### 

	// @396 'h' (4 pixels wide)
	0x80, // #   
	0x80, // #   
	0xE0, // ### 
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x00, //     
	0x00, //     

	// @405 'i' (1 pixels wide)
	0x80, // #
	0x00, //  
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x00, //  

	// @414 'j' (2 pixels wide)
	0x40, //  #
	0x00, //   
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x40, //  #
	0x80, // # 

	// @423 'k' (4 pixels wide)
	0x80, // #   
	0x80, // #   
	0x90, // #  #
	0xA0, // # # 
	0xC0, // ##  
	0xA0, // # # 
	0x90, // #  #
	0x00, //     
	0x00, //     

	// @432 'l' (1 pixels wide)
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x80, // #
	0x00, //  
	0x00, //  

	// @441 'm' (7 pixels wide)
	0x00, //        
	0x00, //        
	0xFC, // ###### 
	0x92, // #  #  #
	0x92, // #  #  #
	0x92, // #  #  #
	0x92, // #  #  #
	0x00, //        
	0x00, //        

	// @450 'n' (4 pixels wide)
	0x00, //     
	0x00, //     
	0xE0, // ### 
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x00, //     
	0x00, //     

	// @459 'o' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x60, //  ## 
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x60, //  ## 
	0x00, //     
	0x00, //     

	// @468 'p' (4 pixels wide)
	0x00, //     
	0x00, //     
	0xE0, // ### 
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0xE0, // ### 
	0x80, // #   
	0x80, // #   

	// @477 'q' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x70, //  ###
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x70, //  ###
	0x10, //    #
	0x10, //    #

	// @486 'r' (2 pixels wide)
	0x00, //   
	0x00, //   
	0xC0, // ##
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0x00, //   
	0x00, //   

	// @495 's' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x70, //  ###
	0x80, // #   
	0x60, //  ## 
	0x10, //    #
	0xE0, // ### 
	0x00, //     
	0x00, //     

	// @504 't' (2 pixels wide)
	0x00, //   
	0x80, // # 
	0xC0, // ##
	0x80, // # 
	0x80, // # 
	0x80, // # 
	0xC0, // ##
	0x00, //   
	0x00, //   

	// @513 'u' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x90, // #  #
	0x70, //  ###
	0x00, //     
	0x00, //     

	// @522 'v' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x88, // #   #
	0x88, // #   #
	0x50, //  # # 
	0x50, //  # # 
	0x20, //   #  
	0x00, //      
	0x00, //      

	// @531 'w' (7 pixels wide)
	0x00, //        
	0x00, //        
	0x92, // #  #  #
	0x92, // #  #  #
	0xAA, // # # # #
	0x44, //  #   # 
	0x44, //  #   # 
	0x00, //        
	0x00, //        

	// @540 'x' (4 pixels wide)
	0x00, //     
	0x00, //     
	0x90, // #  #
	0x90, // #  #
	0x60, //  ## 
	0x90, // #  #
	0x90, // #  #
	0x00, //     
	0x00, //     

	// @549 'y' (5 pixels wide)
	0x00, //      
	0x00, //      
	0x48, //  #  #
	0x48, //  #  #
	0x48, //  #  #
	0x30, //   ## 
	0x20, //   #  
	0x20, //   #  
	0xC0, // ##   

	// @558 'z' (4 pixels wide)
	0x00, //     
	0x00, //     
	0xF0, // ####
	0x10, //    #
	0x60, //  ## 
	0x80, // #   
	0xF0, // ####
	0x00, //     
	0x00, //     
};


// Character descriptors for Microsoft Sans Serif 7pt
// { [Char width in bits], [Offset into microsoftSansSerif_7ptCharBitmaps in bytes] }
const FONT_CHAR_INFO microsoftSansSerif_7ptDescriptors[] =
{
	{ 4, 0 }, 		// 0 
	{ 2, 9 }, 		// 1 
	{ 4, 18 }, 		// 2 
	{ 4, 27 }, 		// 3 
	{ 5, 36 }, 		// 4 
	{ 4, 45 }, 		// 5 
	{ 4, 54 }, 		// 6 
	{ 4, 63 }, 		// 7 
	{ 4, 72 }, 		// 8 
	{ 4, 81 }, 		// 9 
	{ 0, 0 }, 		// : 
	{ 0, 0 }, 		// ; 
	{ 0, 0 }, 		// < 
	{ 0, 0 }, 		// = 
	{ 0, 0 }, 		// > 
	{ 0, 0 }, 		// ? 
	{ 0, 0 }, 		// @ 
	{ 7, 90 }, 		// A 
	{ 4, 99 }, 		// B 
	{ 5, 108 }, 		// C 
	{ 5, 117 }, 		// D 
	{ 4, 126 }, 		// E 
	{ 4, 135 }, 		// F 
	{ 5, 144 }, 		// G 
	{ 5, 153 }, 		// H 
	{ 1, 162 }, 		// I 
	{ 4, 171 }, 		// J 
	{ 5, 180 }, 		// K 
	{ 4, 189 }, 		// L 
	{ 7, 198 }, 		// M 
	{ 5, 207 }, 		// N 
	{ 5, 216 }, 		// O 
	{ 5, 225 }, 		// P 
	{ 5, 234 }, 		// Q 
	{ 5, 243 }, 		// R 
	{ 4, 252 }, 		// S 
	{ 5, 261 }, 		// T 
	{ 5, 270 }, 		// U 
	{ 7, 279 }, 		// V 
	{ 9, 288 }, 		// W 
	{ 6, 306 }, 		// X 
	{ 5, 315 }, 		// Y 
	{ 4, 324 }, 		// Z 
	{ 0, 0 }, 		// [ 
	{ 0, 0 }, 		// \ 
	{ 0, 0 }, 		// ] 
	{ 0, 0 }, 		// ^ 
	{ 0, 0 }, 		// _ 
	{ 0, 0 }, 		// ` 
	{ 4, 333 }, 		// a 
	{ 4, 342 }, 		// b 
	{ 4, 351 }, 		// c 
	{ 4, 360 }, 		// d 
	{ 4, 369 }, 		// e 
	{ 2, 378 }, 		// f 
	{ 4, 387 }, 		// g 
	{ 4, 396 }, 		// h 
	{ 1, 405 }, 		// i 
	{ 2, 414 }, 		// j 
	{ 4, 423 }, 		// k 
	{ 1, 432 }, 		// l 
	{ 7, 441 }, 		// m 
	{ 4, 450 }, 		// n 
	{ 4, 459 }, 		// o 
	{ 4, 468 }, 		// p 
	{ 4, 477 }, 		// q 
	{ 2, 486 }, 		// r 
	{ 4, 495 }, 		// s 
	{ 2, 504 }, 		// t 
	{ 4, 513 }, 		// u 
	{ 5, 522 }, 		// v 
	{ 7, 531 }, 		// w 
	{ 4, 540 }, 		// x 
	{ 5, 549 }, 		// y 
	{ 4, 558 }, 		// z 
};

// Font information for Microsoft Sans Serif 7pt
const FONT_INFO microsoftSansSerif_7ptFontInfo =
{
	2, //  Character height
	'0', //  Start character
	'z', //  End character
	2, //  Width, in pixels, of space character
	microsoftSansSerif_7ptDescriptors, //  Character descriptor array
	microsoftSansSerif_7ptBitmaps, //  Character bitmap array
};
