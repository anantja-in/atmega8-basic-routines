
void read_rtc(unsigned char *a);
void write_rtc(unsigned char);

void write_rtc(unsigned char a)
{
   TWCR|=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);    /*SET THE START BIT*/
   while(!(TWCR&(1<<TWINT)));
    TWDR=0XDO;    /*SLAVE ADDRESS*/
	TWCR|=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT));
	TWDR=0X00;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWDR=0X55;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWDR=0X34;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWDR=0X23;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWDR=0X01;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWCR=0X06;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWDR=0X07;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWDR=0X09;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	
}

void read_rtc(unsigned char *a)
{

    unsigned char a[10];
    TWCR|=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
   	while (!TWCR&(1<<TWINT)));
	TWDR=OXD0;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWDR=0X00;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWDR=0XD1;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	a[0]=TWDR;
	for(i=1;i<7;i++)
	{
	    TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
        TWCR=(1<<TWINT)|(1<<TWEN);
	    while(!(TWCR&(1<<TWINT)));
		a[i]=TWDR;
		TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	}
	TWCR|=(1<<TWINT)|(1<<TWEN)&(~(1<<TWEA));
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	
	}
	
	