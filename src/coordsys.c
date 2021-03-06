
#include <math.h>

#include "coordsys.h"



ref_frame * init_ref_frame(void){
    ref_frame * frame = calloc(1, sizeof(ref_frame));
    //frame->transform = calloc(1,sizeof(T_mat));
    
    frame->transform = calloc(3,sizeof(double *));
    for (unsigned int i=0; i<3; i++){
        frame->transform[i] = calloc(1,sizeof(double));
    }
        
    // Set the ref frame to neutral (no translation or rotation)
     frame->transform[0][0] =1;
     frame->transform[1][1] = 1;
     frame->transform[2][2] = 1;
    
    return frame;
}

int free_ref_frame(ref_frame * frame){
    //free(frame->transform);
    free(frame);
    return 0;
}


void transform_frame(ref_frame * frame, double x, double y, double z, double a, double b, double g){
    
    // Get a temporary transformation matrix  
    T_mat T_ = calloc(3,sizeof(double *));
    for (unsigned int i=0; i<3; i++){
        T_[i] = calloc(4,sizeof(double));
    }
    
    T_mat T = frame->transform;
    
    /*
    T_[0][0] = T[0][0]*cos(a)*cos(b) - T[0][2]*sin(b) + T[0][1]*cos(b)*sin(a);
    T_[0][1] = T[0][1]*(cos(a)*cos(g) + sin(a)*sin(b)*sin(g)) - T[0][0]*(cos(g)*sin(a) - cos(a)*sin(b)*sin(g)) + T[0][2]*cos(b)*sin(g);
    T_[0][2] = T[0][0]*(sin(a)*sin(g) + cos(a)*cos(g)*sin(b)) - T[0][1]*(cos(a)*sin(g) - cos(g)*sin(a)*sin(b)) + T[0][2]*cos(b)*cos(g);
    T_[0][3] = T[0][3] + T[0][0]*x + T[0][1]*y + T[0][2]*z;
    
    T_[1][0] = T[1][0]*cos(a)*cos(b) - T[1][2]*sin(b) + T[1][1]*cos(b)*sin(a);
    T_[1][1] = T[1][1]*(cos(a)*cos(g) + sin(a)*sin(b)*sin(g)) - T[1][0]*(cos(g)*sin(a) - cos(a)*sin(b)*sin(g)) + T[1][2]*cos(b)*sin(g);
    T_[1][2] = T[1][0]*(sin(a)*sin(g) + cos(a)*cos(g)*sin(b)) - T[1][1]*(cos(a)*sin(g) - cos(g)*sin(a)*sin(b)) + T[1][2]*cos(b)*cos(g);
    T_[1][3] = T[1][3] + T[1][0]*x + T[1][1]*y + T[1][2]*z;
    
    T_[2][0] = T[2][0]*cos(a)*cos(b) - T[2][2]*sin(b) + T[2][1]*cos(b)*sin(a);
    T_[2][1] = T[2][1]*(cos(a)*cos(g) + sin(a)*sin(b)*sin(g)) - T[2][0]*(cos(g)*sin(a) - cos(a)*sin(b)*sin(g)) + T[2][2]*cos(b)*sin(g);
    T_[2][2] = T[2][0]*(sin(a)*sin(g) + cos(a)*cos(g)*sin(b)) - T[2][1]*(cos(a)*sin(g) - cos(g)*sin(a)*sin(b)) + T[2][2]*cos(b)*cos(g);
    T_[2][3] = T[2][3] + T[2][0]*x + T[2][1]*y + T[2][2]*z;
*/
        T_[0][0] = T[0][0]*cos(b)*cos(g) - T[0][2]*sin(g) + T[0][1]*cos(g)*sin(b);
    T_[0][1] = T[0][1]*(cos(b)*cos(a) + sin(b)*sin(g)*sin(a)) - T[0][0]*(cos(a)*sin(b) - cos(b)*sin(g)*sin(a)) + T[0][2]*cos(g)*sin(a);
    T_[0][2] = T[0][0]*(sin(b)*sin(a) + cos(b)*cos(a)*sin(g)) - T[0][1]*(cos(b)*sin(a) - cos(a)*sin(b)*sin(g)) + T[0][2]*cos(g)*cos(a);
    T_[0][3] = T[0][3] + T[0][0]*x + T[0][1]*y + T[0][2]*z;
    
    T_[1][0] = T[1][0]*cos(b)*cos(g) - T[1][2]*sin(g) + T[1][1]*cos(g)*sin(b);
    T_[1][1] = T[1][1]*(cos(b)*cos(a) + sin(b)*sin(g)*sin(a)) - T[1][0]*(cos(a)*sin(b) - cos(b)*sin(g)*sin(a)) + T[1][2]*cos(g)*sin(a);
    T_[1][2] = T[1][0]*(sin(b)*sin(a) + cos(b)*cos(a)*sin(g)) - T[1][1]*(cos(b)*sin(a) - cos(a)*sin(b)*sin(g)) + T[1][2]*cos(g)*cos(a);
    T_[1][3] = T[1][3] + T[1][0]*x + T[1][1]*y + T[1][2]*z;
    
    T_[2][0] = T[2][0]*cos(b)*cos(g) - T[2][2]*sin(g) + T[2][1]*cos(g)*sin(b);
    T_[2][1] = T[2][1]*(cos(b)*cos(a) + sin(b)*sin(g)*sin(a)) - T[2][0]*(cos(a)*sin(b) - cos(b)*sin(g)*sin(a)) + T[2][2]*cos(g)*sin(a);
    T_[2][2] = T[2][0]*(sin(b)*sin(a) + cos(b)*cos(a)*sin(g)) - T[2][1]*(cos(b)*sin(a) - cos(a)*sin(b)*sin(g)) + T[2][2]*cos(g)*cos(a);
    T_[2][3] = T[2][3] + T[2][0]*x + T[2][1]*y + T[2][2]*z;

 
   
   // Copy result into T
   
   for (unsigned int i=0; i<3; i++){
    for (unsigned int j=0; j<4; j++){
     T[i][j] = T_[i][j];   
    }
   }
   
   // Release temporary transform 
   // TODO?  This causes segfault, why?
       for (unsigned int i=0; i<3; i++){
        free(T_[i]);
    }
    
    
    return;
}

/*
 *  T03 + T00*x + T01*y + T02*z
 T13 + T10*x + T11*y + T12*z
 T23 + T20*x + T21*y + T22*z
                           1
 */

void transform_point(ref_frame * frame, double x, double y, double z, double * x_, double *y_, double *z_){
    
    T_mat T = frame->transform;
    *(x_) = T[0][3] + T[0][0]*x + T[0][1]*y + T[0][2]*z;
    *(y_) = T[1][3] + T[1][0]*x + T[1][1]*y + T[1][2]*z;
    *(z_) = T[2][3] + T[2][0]*x + T[2][1]*y + T[2][2]*z;
    
    return;
}


void print_frame(ref_frame * frame){
    
    
    T_mat T = frame->transform;
    
    printf("\t[[%f,%f,%f,%f],\n",T[0][0],T[0][1],T[0][2],T[0][3]);
     printf("\t[%f,%f,%f,%f],\n",T[1][0],T[1][1],T[1][2],T[1][3]);
      printf("\t[%f,%f,%f,%f],\n",T[2][0],T[2][1],T[2][2],T[2][3]);
      printf("\t[0,0,0,1]]\n");
 return;    
}
