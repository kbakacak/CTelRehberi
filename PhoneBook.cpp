#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <cstdlib>
#include <iostream>


// Fonksiyonlar
int anaMenu();
void kisiEkle();
void goruntule();
void guncelle();
void sil();
void arama();
int noKontrol(char[12]);
int dogumTarihiKontrol(char[12]);

FILE *dosyaptr; // Her yerde açmak yerine global olarak açtım.

struct telefonRehberi
{
	char ad[20],soyAd[20],evTel[12],cepTel[12],isTel[12],ePosta[30],dogumTarihi[12];
}rehber;
void main()
{
	system("color 74"); // Renk 1. arka plan 2. olan yazı rengi.
	int secim;
	secim=anaMenu();
	switch(secim)
	{
	case 1: kisiEkle(); break;
	case 2: goruntule(); break;
	case 3: guncelle(); break;
	case 4: sil(); break;
	case 5: arama(); break;
	case 0: exit(1); break;
	default : printf("0-5 Arasinda giriniz"); main(); printf("\n"); break;
	}
	getch();
}

int anaMenu() // Menu yapısı
{
	int tercih;
	printf("Secenekler\n");
	printf("1-Kisi Ekleme\n");
	printf("2-Goruntule\n");
	printf("3-Guncelle\n");
	printf("4-Kisi Sil\n");
	printf("5-Arama\n");
	printf("0-Cikis\n");

	printf("Tercihiniz : ");
	scanf_s("%d",&tercih);
	return tercih;
} 

void kisiEkle()
{
	dosyaptr = fopen("rehber.txt","a+"); // Dosyayı açıyoruz.
	char devam='E'; // Aşağıda ki döngüye girmesi için başlangıç değeri E.
	int devamKontrol=1; // Aşağıda ki döngülerde kontrol yapısı.

	if(dosyaptr == NULL)
		printf("Dosya acilamadi.");

	else
	{
		while(devam != 'H') // Burada kişi ekleme için bilgiler isteniyor.
		{
			printf("Kisinin adi : "); // Kullanıcıdan isim alındı.
			scanf("%s",rehber.ad); // scanf ile rehber.ad değişkenine yazıldı.
			fprintf(dosyaptr,"%s\t", rehber.ad); // scanf ile yazılan değişken dosyaya yazılıyor.

			printf("Kisinin soyadi : ");
			scanf("%s",rehber.soyAd);
			fprintf(dosyaptr,"%s\t", rehber.soyAd);

			devamKontrol=1;
			while(devamKontrol == 1) // Burası tamamen kontrol amaçlı numaranın içersinde harf var mı? rakam sayısı doğru mu? diye.
			{
				printf("Kisinin ev telefonu : ");
				scanf("%s",rehber.evTel);
				devamKontrol = noKontrol(rehber.evTel);
			}
			fprintf(dosyaptr,"%s\t", rehber.evTel);

			devamKontrol=1; // Alttaki döngüye kontrol etmesi için dışarıda 1 olarak tanımlanıyor.
			while(devamKontrol == 1)
			{
				printf("Kisinin cep telefonu : ");
				scanf("%s",rehber.cepTel);
				devamKontrol = noKontrol(rehber.cepTel);
			}
			fprintf(dosyaptr,"%s\t", rehber.cepTel);

			devamKontrol=1;
			while(devamKontrol == 1)
			{
				printf("Kisinin is telefonu : ");
				scanf("%s",rehber.isTel);
				devamKontrol = noKontrol(rehber.isTel);
			}
			fprintf(dosyaptr,"%s\t", rehber.isTel);

			printf("Kisinin e-posta adresi : ");
			scanf("%s",rehber.ePosta);
			fprintf(dosyaptr,"%s\t", rehber.ePosta);

			devamKontrol=1;
			while(devamKontrol == 1)
			{
				printf("Kisinin dogum tarihi (GG-AA-YYYY): "); // Belirtilen format dışında girilmesine izin vermeyecek.
				scanf("%s",rehber.dogumTarihi);
				devamKontrol = dogumTarihiKontrol(rehber.dogumTarihi);
			}
			fprintf(dosyaptr,"%s\t\n", rehber.dogumTarihi);

			printf("Yeni kisi eklemek istiyor musunuz? (e/h): ");
			flushall();
			devam=getchar(); // devam değişkenine aktarıldı.
			devam=toupper(devam); // Buyuk harfe çevrildi.
		}
	}

	fclose(dosyaptr); // Dosya kapandı.
	printf("Menuye donmek icin bir tusa basiniz.");
	getch();
	system("cls"); // Ekran temizlendi.
	main();
}

void goruntule()
{
	struct telefonRehberi rehberTemp[50]; // 50 kişi yeterli diye düşündüm fazlasıda olabilir tabi ki.
	struct telefonRehberi rehberTemp2;
	int kisiadedi=0; // Rehberide kaç kişi olacağını sayacağız.
	int i=0;

	dosyaptr = fopen("rehber.txt","r");
	if(dosyaptr == NULL)
		printf("Dosya acilamadi.");
	else
	{
		rewind(dosyaptr);
		
		// while döngüsü içersinde belirtilen ile dosya taranıyor. 
		while(fscanf(dosyaptr,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t",rehber.ad,rehber.soyAd,rehber.evTel,rehber.cepTel,rehber.isTel,rehber.ePosta,rehber.dogumTarihi) != EOF )
		{
			memcpy(&rehberTemp[i],&rehber,sizeof(rehber)); // RehberTemp'e rehberdeki bilgileri kopyalıyor.
			i++;
			kisiadedi++;
		}
		
		// Bu 2 for ile de alfabetik olarak sıralama yapmaktadır.
		for(int j=0; j<kisiadedi; j++)
		{
			for(i=0; i<kisiadedi; i++)
			{
				if(strcmp(rehberTemp[i].ad,rehberTemp[i+1].ad) > 0)
				{
					//memcpy fonksiyonu struct kopyalaması yapıyor.
					memcpy(&rehberTemp2,&rehberTemp[i],sizeof(rehberTemp[i])); 
					memcpy(&rehberTemp[i],&rehberTemp[i+1],sizeof(rehberTemp[i+1]));
					memcpy(&rehberTemp[i+1],&rehberTemp2,sizeof(rehberTemp2));
				}
			}
		}

		printf("%20s%20s%12s%12s%12s%31s%13s\n","Ad","Soyad","Ev Tel","Cep Tel","Is Tel","E-Posta","Dogum Tarihi"); // Üstte duracak şekilde yazıldı.
		
		for(i=0; i<kisiadedi; i++)
		{
			printf("%20s%20s%12s%12s%12s%31s%13s\n",rehberTemp[i].ad,rehberTemp[i].soyAd,rehberTemp[i].evTel,rehberTemp[i].cepTel,rehberTemp[i].isTel,rehberTemp[i].ePosta,rehberTemp[i].dogumTarihi);
		}
	}
	fclose(dosyaptr);
	printf("Menuye donmek icin bir tusa basiniz.");
	getch();
	system("cls"); // Ekran temizlendi.
	main();
}

void guncelle()
{
	char guncellenecekAd[20];
	char guncellenecekSoyAd[20];
	dosyaptr = fopen("rehber.txt","r+");

	FILE *dosyaptrTemp;
	dosyaptrTemp = fopen("rehberTemp.txt","w+");

	int devamKontrol=1; // Numaraları kontrol edecek.
	int adetSayac=0; // Girilen kişiden eğer birden fazla ise bunun sayesinde öğreneceğiz.

	if(dosyaptr == NULL)
		printf("Dosya acilamadi.");
	else
	{
		printf("Guncellenecek hesabin adini giriniz : ");
		flushall();
		gets(guncellenecekAd);

		// Burada ki while döngüsü ile öncelikle öncelikle kontrol ediyoruz.
		while(fscanf(dosyaptr,"%s",rehber.ad) !=EOF)
		{
			fscanf(dosyaptr,"%s",rehber.soyAd);
			fscanf(dosyaptr,"%s",rehber.evTel);
			fscanf(dosyaptr,"%s",rehber.cepTel);
			fscanf(dosyaptr,"%s",rehber.isTel);
			fscanf(dosyaptr,"%s",rehber.ePosta);
			fscanf(dosyaptr,"%s",rehber.dogumTarihi);
			if(!strcmp(guncellenecekAd,rehber.ad))
			{
				printf("Soyadi : %s\n",rehber.soyAd);
				printf("Ev Telefonu : %s\n",rehber.evTel);
				printf("Cep Telefonu : %s\n",rehber.cepTel);
				printf("Is Telefonu : %s\n",rehber.isTel);
				printf("E-Posta Adresi : %s\n",rehber.ePosta);
				printf("Dogum Tarihi : %s\n",rehber.dogumTarihi);
				adetSayac++; // Burada kaç tane olduğunu öğreniyoruz.
			}
		}

		rewind(dosyaptr); // Dosya imlecini başa alıyoruz çünkü tekrar tarama yapacağız.

		if(adetSayac==0) // 0 ise hiç anlamında buraya girecek.
			printf("Guncellenecek isim bulunamadi.");
		else if(adetSayac==1) // 1 ise buraya girecek ve kişi ekleme gibi  düzenleyeceğimiz kişiyi alacağız.
		{
			while(fscanf(dosyaptr,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t",rehber.ad,rehber.soyAd,rehber.evTel,rehber.cepTel,rehber.isTel,rehber.ePosta,rehber.dogumTarihi) != EOF )
			{
				if(!strcmp(guncellenecekAd,rehber.ad))
				{
					printf("Guncellenecek isim : %s\t%s\t%s\t%s\t%s\t%s\t%s\n",rehber.ad,rehber.soyAd,rehber.evTel,rehber.cepTel,rehber.isTel,rehber.ePosta,rehber.dogumTarihi);

					// Bilgileri güncellemek için tekrar alacağız.
					printf("Kisinin adi : ");
					scanf("%s",rehber.ad);
					fprintf(dosyaptrTemp,"%s\t", rehber.ad);

					printf("Kisinin soyadi : ");
					scanf("%s",rehber.soyAd);
					fprintf(dosyaptrTemp,"%s\t", rehber.soyAd);

					devamKontrol=1;
					while(devamKontrol == 1)
					{
						printf("Kisinin ev telefonu : ");
						scanf("%s",rehber.evTel);
						devamKontrol = noKontrol(rehber.evTel);
					}
					fprintf(dosyaptrTemp,"%s\t", rehber.evTel);

					devamKontrol=1;
					while(devamKontrol == 1)
					{
						printf("Kisinin cep telefonu : ");
						scanf("%s",rehber.cepTel);
						devamKontrol = noKontrol(rehber.cepTel);
					}
					fprintf(dosyaptrTemp,"%s\t", rehber.cepTel);

					devamKontrol=1;
					while(devamKontrol == 1)
					{
						printf("Kisinin is telefonu : ");
						scanf("%s",rehber.isTel);
						devamKontrol = noKontrol(rehber.isTel);
					}
					fprintf(dosyaptrTemp,"%s\t", rehber.isTel);

					printf("Kisinin e-posta adresi : ");
					scanf("%s",rehber.ePosta);
					fprintf(dosyaptrTemp,"%s\t", rehber.ePosta);

					devamKontrol=1;
					while(devamKontrol == 1)
					{
						printf("Kisinin dogum tarihi (GG-AA-YYYY): ");
						scanf("%s",rehber.dogumTarihi);
						devamKontrol = dogumTarihiKontrol(rehber.dogumTarihi);
					}
					fprintf(dosyaptrTemp,"%s\t\n", rehber.dogumTarihi);
				}
				else
					fprintf(dosyaptrTemp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rehber.ad,rehber.soyAd,rehber.evTel,rehber.cepTel,rehber.isTel,rehber.ePosta,rehber.dogumTarihi);
			}
		}
		else if(adetSayac>1) // 1'den büyük ise buraya girecek.
		{
			printf("Girdiginiz kisiden rehberde %d adet bulunmaktadir.",adetSayac); // Ekrana kaç tane olduğunu yazdırdık.
			printf("Guncellenecek kisinin soyadini giriniz : "); // Soyad alıyoruz çünkü birden fazla aynı isimde insan var.
			gets(guncellenecekSoyAd); // gets ile aktardık.

			// Burası tamamen kişi ekleme gibi çalışıyor. Ondan öncekilere kadar olanları diğer dosyaya yazıyor, ona gelince bizden
			// istiyor, biz giriyoruz, arkasından devam ediyor diğerlerini dosyaya yazmaya.
			while(fscanf(dosyaptr,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t",rehber.ad,rehber.soyAd,rehber.evTel,rehber.cepTel,rehber.isTel,rehber.ePosta,rehber.dogumTarihi) != EOF )
			{
				if(!strcmp(guncellenecekAd,rehber.ad) && !strcmp(guncellenecekSoyAd,rehber.soyAd))
				{
					printf("Guncellenecek isim : %s\t%s\t%s\t%s\t%s\t%s\t%s\n",rehber.ad,rehber.soyAd,rehber.evTel,rehber.cepTel,rehber.isTel,rehber.ePosta,rehber.dogumTarihi);
					// Bilgileri güncellemek için tekrar alacağız.
					printf("Kisinin adi : ");
					scanf("%s",rehber.ad);
					fprintf(dosyaptrTemp,"%s\t", rehber.ad);

					printf("Kisinin soyadi : ");
					scanf("%s",rehber.soyAd);
					fprintf(dosyaptrTemp,"%s\t", rehber.soyAd);

					devamKontrol=1;
					while(devamKontrol == 1)
					{
						printf("Kisinin ev telefonu : ");
						scanf("%s",rehber.evTel);
						devamKontrol = noKontrol(rehber.evTel);
					}
					fprintf(dosyaptrTemp,"%s\t", rehber.evTel);

					devamKontrol=1;
					while(devamKontrol == 1)
					{
						printf("Kisinin cep telefonu : ");
						scanf("%s",rehber.cepTel);
						devamKontrol = noKontrol(rehber.cepTel);
					}
					fprintf(dosyaptrTemp,"%s\t", rehber.cepTel);

					devamKontrol=1;
					while(devamKontrol == 1)
					{
						printf("Kisinin is telefonu : ");
						scanf("%s",rehber.isTel);
						devamKontrol = noKontrol(rehber.isTel);
					}
					fprintf(dosyaptrTemp,"%s\t", rehber.isTel);

					printf("Kisinin e-posta adresi : ");
					scanf("%s",rehber.ePosta);
					fprintf(dosyaptrTemp,"%s\t", rehber.ePosta);

					devamKontrol=1;
					while(devamKontrol == 1)
					{
						printf("Kisinin dogum tarihi (GG-AA-YYYY): ");
						scanf("%s",rehber.dogumTarihi);
						devamKontrol = dogumTarihiKontrol(rehber.dogumTarihi);
					}
					fprintf(dosyaptrTemp,"%s\t\n", rehber.dogumTarihi);
				}
				else
					fprintf(dosyaptrTemp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rehber.ad,rehber.soyAd,rehber.evTel,rehber.cepTel,rehber.isTel,rehber.ePosta,rehber.dogumTarihi);
			}
		}
	}
	// Gecici dosyamız vardı haliyle isim değişmesi lazım diğer komutların kullanılması için ama öncelikle fclose ile kapatıyoruz.
	fclose(dosyaptr);
	fclose(dosyaptrTemp);
	remove("rehber.txt");
	rename("rehberTemp.txt","rehber.txt"); // rehber.txt her zaman kullandığımız eski ismini verdik.

	fclose(dosyaptr);
	printf("Menuye donmek icin bir tusa basiniz.");
	getch();
	system("cls"); // Ekranı temizledik.
	main();
}

void sil()
{
	char silinecekAd[20];
	char devam;

	dosyaptr = fopen("rehber.txt","r+");

	FILE *dosyaptrTemp;
	dosyaptrTemp = fopen("rehberTemp.txt","w+");

	if(dosyaptr == NULL)
		printf("Dosya acilamadi.");
	else
	{
		printf("Silinecek hesabin adini giriniz : ");
		flushall();
		gets(silinecekAd);

		// Silmek istiyor musunuz diye soracak.
		printf("Silmek istediginize emin misiniz ? (E/H) : ");
		flushall();
		devam=getchar();
		devam=toupper(devam);

		// Evet dersek buraya girecek ve silecek.
		if(devam == 'E') 
		{
			while(fscanf(dosyaptr,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t",rehber.ad,rehber.soyAd,rehber.evTel,rehber.cepTel,rehber.isTel,rehber.ePosta,rehber.dogumTarihi) != EOF )
			{
				if(!strcmp(silinecekAd,rehber.ad)) // Burada ekrana yazıyor sildiği bilgileri.
					printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\tSilindi!\n",rehber.ad,rehber.soyAd,rehber.evTel,rehber.cepTel,rehber.isTel,rehber.ePosta,rehber.dogumTarihi);
				else
					fprintf(dosyaptrTemp,"%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rehber.ad,rehber.soyAd,rehber.evTel,rehber.cepTel,rehber.isTel,rehber.ePosta,rehber.dogumTarihi);
			}
		}

	}
	// Gecici dosyamız vardı haliyle isim değişmesi lazım diğer komutların kullanılması için ama öncelikle fclose ile kapatıyoruz.
	fclose(dosyaptr);
	fclose(dosyaptrTemp);
	remove("rehber.txt");
	rename("rehberTemp.txt","rehber.txt"); // Eski ismini verdik programın devamlılığı için.

	printf("Menuye donmek icin bir tusa basiniz.");
	getch();
	system("cls"); // Ekranı temizledik.
	main();
}

void arama()
{
	char aranacakAd[20];
	dosyaptr=fopen("rehber.txt","r"); // r modunda açmamız yeterli.
	int adetSayac=0; // Aranan kişi bulunamazsa bunun ile kontrol edecek.

	if(dosyaptr == NULL)
		printf("Dosya acilamadi.");
	else
	{
		printf("Aranacak kisinin ismi : ");
		flushall();
		gets(aranacakAd);

		// Program ada göre arama yaptığı için burada sadece isimi dosya sonuna gelip gelmediğini sorguluyor.
		while(fscanf(dosyaptr,"%s",rehber.ad) !=EOF)
		{
			fscanf(dosyaptr,"%s",rehber.soyAd);
			fscanf(dosyaptr,"%s",rehber.evTel);
			fscanf(dosyaptr,"%s",rehber.cepTel);
			fscanf(dosyaptr,"%s",rehber.isTel);
			fscanf(dosyaptr,"%s",rehber.ePosta);
			fscanf(dosyaptr,"%s",rehber.dogumTarihi);
			if(!strcmp(aranacakAd,rehber.ad))
			{
				printf("Soyadi : %s\n",rehber.soyAd);
				printf("Ev Telefonu : %s\n",rehber.evTel);
				printf("Cep Telefonu : %s\n",rehber.cepTel);
				printf("Is Telefonu : %s\n",rehber.isTel);
				printf("E-Posta Adresi : %s\n",rehber.ePosta);
				printf("Dogum Tarihi : %s\n",rehber.dogumTarihi);
				adetSayac++;
			}
		}
	}

	if(adetSayac==0) // Hiç girmezse döngüye demek ki öyle birisi yok yani 0 olacak burası.
		printf("Aranan kisi bulunamadi.\n");

	fclose(dosyaptr);
	printf("Menuye donmek icin bir tusa basiniz.");
	getch();
	system("cls"); // Ekranı temizledi.
	main();

}

int noKontrol(char numara[12])
{
	int devamKontrol=1;
	int sayac=0;
	int dogru=1,yanlis=0;
	for(int i=0;i<15;i++)
	{

		if(numara[i]>=48 && numara[i]<=57)
			//16 lık tabanda 0'a karşılık gelen 48 olduğu için bu şekilde.
		{
			sayac++; // Sayac arttıyor burada yukarıdakilerden her hangi biri ise.
		}
		else
		{
			if(sayac < 11) // 11 Rakamlı olduğu için bir telefon numarası altında ise buraya girecek.
				printf("Hatali numara\n");
			break; // Döngü kesilecek.
			devamKontrol=0; // Kontrol yapısınıda 0 yapacak.
		}
		if(sayac == 11) // 11'e eşit ise burası doğru.
			devamKontrol=0;
		if(sayac > 11) // 11'den büyük ise de yanlış olduğu için burada belirtildi.
		{
			printf("Hatali numara\n");
			devamKontrol=1;
			break;
		}
	}
	if(devamKontrol==1)
		return dogru;
	else
		return yanlis;
}

int dogumTarihiKontrol(char tarih[12])
{
	int devamKontrol=1; // Aşağıda ki döngülerde kontrol yapısı.
	int sayac=0; // Numaranın doğru olduğunu anlamak için kontrol amaçlı yazıldı.

	int fark1,fark2,toplam1; // Dogum tarihi kontrol edilirken kullanılıyor.
	int fark3,fark4; // Burası ek olarak yıl kontrolü için yazıldı.
	int dogru=1,yanlis=0;

	for(int i=0;i<15;i++)
	{
		if(tarih[i]>=48 && tarih[i]<=57 || tarih[i]==45)
		{
			sayac++;
		}
		else
		{
			if(sayac < 10)
				printf("Hatali Format\n");
			break;
			devamKontrol=0;
		}
		if(sayac == 10)
			devamKontrol=0;
		if(sayac > 11)
		{
			printf("Hatali Format\n");
			devamKontrol=1;
			break;
		}
	}

	if(devamKontrol == 0) // Gun 31 den büyük veya 0 dan kücük ise kontrol edecek.
	{
		fark1=tarih[0]-48;
		fark2=tarih[1]-48;
		toplam1=fark1*10+fark2;

		if(toplam1 > 31 || toplam1 < 1)
		{
			devamKontrol=1;
			printf("Hatali gun girildi.\n");
		}
	}

	if(devamKontrol == 0) // Ay 12 den büyük veya 0 dan kücük ise kontrol edecek.
	{
		fark1=tarih[3]-48;
		fark2=tarih[4]-48;
		toplam1=fark1*10+fark2;

		if(toplam1 > 12 || toplam1 < 1)
		{
			devamKontrol=1;
			printf("Hatali ay girildi.\n");
		}
	}

	if(devamKontrol == 0) // Yıl 2014 den büyük ise kontrol edecek
	{
		fark1=tarih[6]-48;
		fark2=tarih[7]-48;
		fark3=tarih[8]-48;
		fark4=tarih[9]-48;
		toplam1=fark1*1000+fark2*100+fark3*10+fark4;

		if(toplam1 > 2014)
		{
			devamKontrol=1;
			printf("Hatali yil girildi.\n");
		}
	}
	if(devamKontrol==1)
		return dogru;
	else
		return yanlis;

}
