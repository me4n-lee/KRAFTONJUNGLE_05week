// Q 7 - The equivalent pointer expression by using the array element a[i][j][k][2],

// A : *(*(*(*(a+i)+j)+k)+2)

// If, the array element is a[i][j] = *(*(a+i)+j)
// If, the array element is a[i][j][k]= *(*(*(a+i)+j)+k)