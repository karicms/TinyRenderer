#define _CRT_SECURE_NO_WARNINGS  // 在程序的开始部分添加这一行

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 100
#define MAX_BOOKINGS 100

/*
可以输入起飞抵达城市，查询飞机航班情况；
订票：（订票情况可以存在一个数据文件中，结构自己设定）。可以订票，如果该航班已经无票，可以提供相关可以提供相关可选择航班;
退票： 可退票，退票后修改相关数据文件；
当航班信息改变可以修改航班数据文件
*/

typedef struct
{
    char flight_number[20]; // 航班号
    char departure_city[50];// 出发城市
    char arrival_city[50];// 到达城市
    char departure_time[20];// 出发时间
    char arrival_time[20];// 到达时间
    float ticket_price;// 票价
    float discount;// 折扣
    int total_seats;// 总座位数
    int available_seats;// 可用座位数
} Flight;

Flight flights[MAX_FLIGHTS];
int flights_num = 0;

typedef struct
{
    int booking_number; // 订票号
    char passenger_name[50];// 乘客姓名
    char id_number[20];// 乘客身份证号
    int num_tickets;// 订票数
    char flight_number[20];// 航班号
} Booking;  // 订票信息

Booking bookings[MAX_BOOKINGS];
int bookings_num = 0;

void save_flights(Flight flights[], int num_flights)
{
    FILE* file = fopen("D:\\APP\\vs2022p\\project\\flights.dat", "wb");// 打开文件进行写入
    if (file != NULL) 
    {
        fwrite(flights, sizeof(Flight), num_flights, file);// 写入文件
        fclose(file);
        printf("文件保存成功");
    }
    else 
    {
        printf("无法打开文件进行写入。\n");
    }
}

void load_flights(Flight flights[], int* num_flights)
{
    FILE* file = fopen("D:\\APP\\vs2022p\\project\\flights.dat", "rb");
    if (file != NULL)
    {
        *num_flights = fread(flights, sizeof(Flight), MAX_FLIGHTS, file);
        fclose(file);
    }
    else
    {
        *num_flights = 0;
        printf("无法打开文件进行读取。\n");
    }
}

void save_bookings(Booking bookings[], int num_bookings) {
    FILE* file = fopen("D:\\APP\\vs2022p\\project\\bookings.dat", "wb");
    if (file != NULL) {
        fwrite(bookings, sizeof(Booking), num_bookings, file);
        fclose(file);
        printf("文件保存成功");
    }
    else {
        printf("无法打开文件进行写入。\n");
    }
}

void load_bookings(Booking bookings[], int* num_bookings) {
    FILE* file = fopen("D:\\APP\\vs2022p\\project\\bookings.dat", "rb");
    if (file != NULL) {
        *num_bookings = fread(bookings, sizeof(Booking), MAX_BOOKINGS, file);
        fclose(file);
    }
    else {
        *num_bookings = 0;
        printf("无法打开文件进行读取。\n");
    }
}

int menu() // 显示菜单
{
    system("cls");
    int choice;
    printf("欢迎使用航班订票系统\n");
    printf("1.录入航班信息\n");
    printf("2.查询航班信息\n");
    printf("3.订票\n");
    printf("4.退票\n");
    printf("5.修改航班信息\n");
    printf("6.退出\n");
    printf("请输入您的选择：");
    scanf("%d", &choice);
    return choice;
}

void add_flight(Flight flights[], int* num_flights)
{
    if (*num_flights >= MAX_FLIGHTS) {
        printf("系统航班数量已满，无法添加新航班。\n");
        return;
    }

    printf("请输入新航班信息\n");

    // 从用户获取航班详细信息
    printf("航班号: ");
    scanf("%s", &flights[*num_flights].flight_number);

    printf("出发城市: ");
    scanf("%s", &flights[*num_flights].departure_city);

    printf("到达城市: ");
    scanf("%s", &flights[*num_flights].arrival_city);

    printf("出发时间: ");
    scanf("%s", &flights[*num_flights].departure_time);

    printf("到达时间: ");
    scanf("%s", &flights[*num_flights].arrival_time);

    printf("票价: ");
    scanf("%f", &flights[*num_flights].ticket_price);

    printf("折扣: ");
    scanf("%f", &flights[*num_flights].discount);

    printf("总座位数: ");
    scanf("%d", &flights[*num_flights].total_seats);

    // 初始时，将可用座位数设置为总座位数
    flights[*num_flights].available_seats = flights[*num_flights].total_seats;

    // 增加航班数量
    (*num_flights)++;

 
    printf("航班添加成功！\n");
}

void display_flights(Flight flights[], int num_flights)
{
    
    printf("航班信息：\n");
    printf("%-15s%-17s%-17s%-17s%-17s%-15s%-15s%-15s%-15s\n",
        "航班号", "出发c", "到达c", "出发t", "到达t",
        "票价", "折扣", "总座位数", "可用座位数");

    for (int i = 0; i < num_flights; ++i)
    {
        printf("%-15s%-15s%-15s%-15s%-15s%-15.2f%-12.2f%-14d%-14d\n",
            flights[i].flight_number, flights[i].departure_city,
            flights[i].arrival_city, flights[i].departure_time,
            flights[i].arrival_time, flights[i].ticket_price,
            flights[i].discount, flights[i].total_seats,
            flights[i].available_seats);
    }
    system("pause");
}

void search_flight_by_number(Flight flights[], int num_flights)
{
 
    char search_number[20];
    printf("请输入要查询的航班号：");
    scanf("%s", search_number);

    int found = 0;

    // 在航班数组中查找用户输入的航班号
    for (int i = 0; i < num_flights; ++i)
    {
        if (strcmp(flights[i].flight_number, search_number) == 0)
        {
            found = 1;
            printf("航班信息：\n");
            printf("%-15s%-17s%-17s%-17s%-17s%-15s%-15s%-15s%-15s\n",
                "航班号", "出发c", "到达c", "出发t", "到达t",
                "票价", "折扣", "总座位数", "可用座位数");
            printf("%-15s%-15s%-15s%-15s%-15s%-15.2f%-12.2f%-14d%-14d\n",
                flights[i].flight_number, flights[i].departure_city,
                flights[i].arrival_city, flights[i].departure_time,
                flights[i].arrival_time, flights[i].ticket_price,
                flights[i].discount, flights[i].total_seats,
                flights[i].available_seats);
            break;  // 找到航班后结束循环
        }
    }

    if (!found)
    {
        printf("未找到航班号为 %s 的航班。\n", search_number);
    }

    system("pause");
}

void book_ticket(Flight flights[], int num_flights, Booking bookings[], int* num_bookings)
{
    // 展示可用航班信息供用户选择
    display_flights(flights, num_flights);

    // 用户输入订票的航班号和订票数量
    char selected_flight[20];
    int num_tickets;

    printf("请输入要订票的航班号：");
    scanf("%s", selected_flight);

    printf("请输入订票数量：");
    scanf("%d", &num_tickets);

    // 在航班数组中查找用户选择的航班
    int selected_index = -1;
    for (int i = 0; i < num_flights; ++i)
    {
        if (strcmp(flights[i].flight_number, selected_flight) == 0) // 找到航班
        {
            selected_index = i;
            break;
        }
    }

    // 检查航班是否存在，以及是否有足够的可用座位
    if (selected_index == -1) 
    {
        printf("未找到航班号为 %s 的航班。\n", selected_flight);
        return;
    }

    if (flights[selected_index].available_seats < num_tickets)
    {
        printf("该航班座位不足，无法订票。\n");
        return;
    }

    // 创建一个新的订票记录
    Booking new_booking;
    new_booking.booking_number = *num_bookings + 1; // 自动生成订票号
    strcpy(new_booking.flight_number, selected_flight);// 将航班号复制到订票记录中
    new_booking.num_tickets = num_tickets;// 将订票数量复制到订票记录中

    printf("请输入乘客姓名：");
    scanf("%s", new_booking.passenger_name);

    printf("请输入乘客身份证号：");
    scanf("%s", new_booking.id_number);

    // 更新相应航班的可用座位数
    flights[selected_index].available_seats -= num_tickets;

    // 将订票记录保存到订票数组中
    bookings[*num_bookings] = new_booking;
    (*num_bookings)++;

    printf("订票成功！\n");
}

void cancel_ticket(Flight flights[], int num_flights, Booking bookings[], int* num_bookings)// 退票
{
    // 展示订票信息供用户选择
    printf("订票信息：\n");
    printf("%-15s%-15s%-15s%-17s%-15s\n",
        "订票号", "航班号", "乘客姓名", "身份证号", "订票数量");

    for (int i = 0; i < *num_bookings; ++i) 
    {
        printf("%-14d%-14s%-14s%-14s%-14d\n",
            bookings[i].booking_number, bookings[i].flight_number,
            bookings[i].passenger_name, bookings[i].id_number,
            bookings[i].num_tickets);
    }

    // 用户输入要退票的订票号
    int cancel_booking_number;
    printf("请输入要退票的订票号：");
    scanf("%d", &cancel_booking_number);

    // 在订票数组中查找用户选择的订票记录
    int cancel_index = -1; // 订票记录在数组中的下标
    for (int i = 0; i < *num_bookings; ++i) 
    {
        if (bookings[i].booking_number == cancel_booking_number)
        {
            cancel_index = i;
            break;
        }
    }

    // 检查订票记录是否存在
    if (cancel_index == -1) 
    {
        printf("未找到订票号为 %d 的订票记录。\n", cancel_booking_number);
        return;
    }

    // 还原相应航班的可用座位数
    for (int i = 0; i < num_flights; ++i) 
    {
        if (strcmp(flights[i].flight_number, bookings[cancel_index].flight_number) == 0) // 找到航班
        {
            flights[i].available_seats += bookings[cancel_index].num_tickets;
            break;
        }
    }

    // 移除订票记录
    for (int i = cancel_index; i < *num_bookings - 1; ++i)
    {
        bookings[i] = bookings[i + 1];
    }
    (*num_bookings)--;
    printf("退票成功！\n");
}

void modify_flight(Flight flights[], int num_flights)
{
    // 展示航班信息供用户选择
    display_flights(flights, num_flights);

    // 用户输入要修改的航班号
    char modify_flight_number[20];
    printf("请输入要修改的航班号：");
    scanf("%s", modify_flight_number);

    // 在航班数组中查找用户选择的航班
    int modify_index = -1; // 航班在数组中的下标
    for (int i = 0; i < num_flights; ++i) 
    {
        if (strcmp(flights[i].flight_number, modify_flight_number) == 0)// 找到航班
        {
            modify_index = i;
            break;
        }
    }

    // 检查航班是否存在
    if (modify_index == -1) 
    {
        printf("未找到航班号为 %s 的航班。\n", modify_flight_number);
        return;
    }

    // 用户选择要修改的信息
    int modify_choice;
    printf("请选择要修改的信息：\n");
    printf("1.起飞时间\n");
    printf("2.到达时间\n");
    printf("3.票价\n");
    printf("请输入您的选择：");
    scanf("%d", &modify_choice);

    // 根据用户选择进行相应的修改
    switch (modify_choice)
    {
    case 1:
        printf("请输入新的起飞时间：");
        scanf("%s", flights[modify_index].departure_time);
        break;
    case 2:
        printf("请输入新的到达时间：");
        scanf("%s", flights[modify_index].arrival_time);
        break;
    case 3:
        printf("请输入新的票价：");
        scanf("%f", &flights[modify_index].ticket_price);
        break;
        // 其他修改选项...
    default:
        printf("无效的选择。\n");
        return;
    }
    printf("航班信息修改成功！\n");
}


void keydown(int a)
{
    switch (a)
    {
    case 1:
        add_flight(flights, &flights_num);
        break;
    case 2:
        search_flight_by_number(flights, flights_num);
        break;
    case 3:
        book_ticket(flights, flights_num, bookings, &bookings_num);
        break;
    case 4:
        cancel_ticket(flights, flights_num, bookings, &bookings_num);
        break;
    case 5:
        modify_flight(flights, flights_num);
        break;
    case 6:
       exit(0);
        break;
    default:
        printf("输入错误，请重新输入\n");
        break;
    }
}

int main()
{
    Flight flights[MAX_FLIGHTS];
    int num_flights = 0;

    Booking bookings[MAX_BOOKINGS];
    int num_bookings = 0;

    // 加载航班和订票信息

    while (1)
    {
        load_flights(flights, &num_flights);
        load_bookings(bookings, &num_bookings);
        keydown(menu());
        save_flights(flights, num_flights);
        save_bookings(bookings, num_bookings);
    }

    // 保存航班和订票信息
   

    return 0;
}
