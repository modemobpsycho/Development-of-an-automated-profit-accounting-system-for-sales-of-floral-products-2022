#pragma once
#include <map>
#include <string>
#include "Account.h"
#include "Admin.h"
#include "Seller.h"
#include "Buyer.h"
#include "Menu.h"

using namespace std;

void authentification(map <string, Account>& accounts, map <string, User>& users, map <string, FlowerAdmin>& flowers);  //���� � �������
void user_registration(map <string, User>& users);      //�����������
