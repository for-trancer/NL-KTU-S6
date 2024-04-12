#include <stdio.h>

void main()
{
	int in,out,b_size,store=0,drop,n;
	printf("Enter The Bucket Size , Outgoing Rate And No Of Inputs : ");
	scanf("%d %d %d",&b_size,&out,&n);
	while(n!=0)
	{
		printf("\nEnter The Incoming Packet Rate : ");
		scanf("%d",&in);
		if(in<=(b_size-store))
		{
			store+=in;
			printf("Bucket Buffer Size %d out of %d\n",store,b_size);
		}
		else
		{
			drop=in-(b_size-store);
			printf("Dropped Packet %d\n",drop);
			printf("Bucket Buffer Size %d out of %d\n",store,b_size);
			store=b_size; 
		}
		store-=out;
		if(store<0)
		{
			store=0;
		}
		printf("After Outgoing, %d Packets Out of %d Are In The Buffer\n",store,b_size);
		n--;
	}
}
