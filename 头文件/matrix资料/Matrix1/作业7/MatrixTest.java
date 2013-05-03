class Matrix{
	 int rows,cols;
	 int data[][];
	 Matrix(){}
	 Matrix(int rows,int cols)
	 {
           this.rows=rows;
           this.cols=cols;
           data=new int[rows][cols];
	 }
         Matrix(int rows,int cols,int data[][])
         {
      	   this.rows=rows;
  	   this.cols=cols;
  	   this.data=data;
         }
 
         int getData(int row,int col)
         {
          return data[row][col];	
         }
         int setData(int row,int col,int value)
         {
  	  data[row][col]=value;
  	  return value;
         }  	       
  
         Matrix multiply(Matrix m)
         {
    	  int i,j,k;
  	  Matrix result=new Matrix(rows,m.cols);
  	  for(i=0;i<rows;i++)
  	    for(j=0;j<m.cols;j++)
  	     for(k=0;k<cols;k++)
  	       result.data[i][j]+=data[i][k]*m.data[k][j];
  	  return result;
         }
  
          public String toString()
          {
  	      String result="";
  	      for(int i=0;i<rows;i++){
  	   	for(int j=0;j<cols;j++)
  	   	   result+=+data[i][j]+"  ";
  	        result+="\n";
  	        }
  	      return result;
  	  }

	 void Fuzhi(int rows,int cols)
	 {
	  int i,j;
	  for(i=0;i<rows;i++)
            for(j=0;j<cols;j++)
              data[i][j]=(int)(Math.random()*10);
	 }	
}

public class MatrixTest{
        public static void main(String[] args){
           int i,j,a,b,x,y;
           System.out.print("�������A������:");
           a=KeyInput.readInt();
           System.out.print("�������A������:");
           b=KeyInput.readInt();
           Matrix A=new Matrix(a,b);
           A.Fuzhi(a,b);
           System.out.println("***����A***\n"+A.toString());
           
           System.out.print("�������B������:");
           x=KeyInput.readInt();
           System.out.print("�������B������:");
           y=KeyInput.readInt();
           Matrix B=new Matrix(x,y);
           B.Fuzhi(x,y);
           System.out.println("***����B***\n"+B.toString());
           
           if(b!=x)
    	     System.out.println("�����Ͼ����������,�������!");
    	   else
             System.out.println("��˽��Ϊ:\n"+A.multiply(B).toString());
         }
}