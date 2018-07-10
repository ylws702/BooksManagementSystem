#pragma once
#include "AdminMap.h"
#include "UserMap.h"
#include "BookMap.h"
#include <cstring>
#include <list>
class AdminHelper
{
public:
	//默认构造函数
	AdminHelper() {}
	//************************************
	// 函数名 : Login
	// 功  能 : 登录
	// 返回值 : bool : 是否成功,失败可能因为该编号的图书管理员不存在
	//                或用户名不正确或密码不正确
	// 参  数 : const ID id : 编号
	// 参  数 : const char * name : 用户名
	// 参  数 : const char * password : 密码
	//************************************
	bool Login(const ID id,const char * name, const char* password);
	//************************************
	// 函数名 : Logout
	// 功  能 : 注销
	// 返回值 : bool : 是否成功
	//************************************
	bool Logout();
	//************************************
	// 函数名 : TestPassword
	// 功  能 : 验证password是否为当前登录图书管理员的密码
	// 返回值 : bool : 密码是否验证成功,未登录会返回false
	// 参  数 : const char * password : 要验证的密码
	//************************************
	bool TestPassword(const char* password);
	//************************************
	// 函数名 : ChangePassword
	// 功  能 : 更改密码,会自动保存至文件
	// 返回值 : bool : 是否成功,失败可能因为未登录或新密码过长或写入文件失败
	// 参  数 : const char * oldpw : 旧密码
	// 参  数 : const char * newpw : 新密码
	//************************************
	bool ChangePassword(const char* oldpw, const char* newpw);
	//************************************
	// 函数名 : AddBook
	// 功  能 : 使用全部信息添加图书
	// 返回值 : bool : 是否成功,未登录或图书已在列表中或信息字符串过长会返回false
	// 参  数 : const ID id : 编号
	// 参  数 : const char * title : 标题
	// 参  数 : const char * author : 作者
	// 参  数 : const char * press : 出版社
	// 参  数 : const char * date : 出版日期
	// 参  数 : const char * type : 类型
	// 参  数 : const int number : 总数
	//************************************
	bool AddBook(const ID id, 
		const char* title,
		const char* author,
		const char* press,
		const char* date,
		const char* type,
		const int number);
	//************************************
	// 函数名 : RemoveBook
	// 功  能 : 删除指定编号的图书并删除相应的用户借阅记录
	// 返回值 : bool : 是否成功,未登录或指定编号的图书不存在会返回false
	// 参  数 : const ID id : 图书编号
	//************************************
	bool RemoveBook(const ID id);
	//************************************
	// 函数名 : RemoveAllBooks
	// 功  能 : 删除所有图书并删除所有用户借阅记录
	// 返回值 : bool : 是否成功,未登录或会返回false
	//************************************
	bool RemoveAllBooks();
	//************************************
	// 函数名 : GetBookTitle
	// 功  能 : 获取指定编号的图书的标题
	// 返回值 : const char* : 标题,未登录或指定编号的图书不存在会返回nullptr
	// 参  数 : const ID id : 编号
	//************************************
	const char* GetBookTitle(const ID id)const;
	//************************************
	// 函数名 : GetBookAuthor
	// 功  能 : 获取指定编号的图书的作者
	// 返回值 : const char* : 作者,未登录或指定编号的图书不存在会返回nullptr
	// 参  数 : const ID id : 编号
	//************************************
	const char* GetBookAuthor(const ID id)const;
	//************************************
	// 函数名 : GetBookPress
	// 功  能 : 获取指定编号的图书的出版社
	// 返回值 : const char* : 出版社,未登录或指定编号的图书不存在会返回nullptr
	// 参  数 : const ID id : 编号
	//************************************
	const char* GetBookPress(const ID id)const;
	//************************************
	// 函数名 : GetBookDate
	// 功  能 : 获取指定编号的图书的出版日期
	// 返回值 : const char* : 出版日期,未登录或指定编号的图书不存在会返回nullptr
	// 参  数 : const ID id : 编号
	//************************************
	const char* GetBookDate(const ID id)const;
	//************************************
	// 函数名 : GetBookType
	// 功  能 : 获取指定编号的图书的类型
	// 返回值 : const char* : 类型,未登录或指定编号的图书不存在会返回nullptr
	// 参  数 : const ID id : 编号
	//************************************
	const char* GetBookType(const ID id)const;
	//************************************
	// 函数名 : GetBookExist
	// 功  能 : 获取指定编号的图书是否在馆内
	// 返回值 : bool : 是否在馆内,未登录会返回false
	// 参  数 : const ID id : 编号
	//************************************
	bool GetBookExist(const ID id)const;
	//************************************
	// 函数名 : SetBookTitle
	// 功  能 : 设置指定编号的图书的标题
	// 返回值 : bool : 是否成功,未登录或标题过长会返回false
	// 参  数 : const ID id : 编号
	// 参  数 : const char * title : 标题
	//************************************
	bool SetBookTitle(const ID id,const char* title);
	//************************************
	// 函数名 : SetBookAuthor
	// 功  能 : 设置指定编号的图书的作者
	// 返回值 : bool : 是否成功,未登录或作者名过长会返回false
	// 参  数 : const ID id : 编号
	// 参  数 : const char * author : 作者
	//************************************
	bool SetBookAuthor(const ID id, const char* author);
	//************************************
	// 函数名 : SetBookPress
	// 功  能 : 设置指定编号的图书的出版社
	// 返回值 : bool : 是否成功,未登录或出版社名过长会返回false
	// 参  数 : const ID id : 编号
	// 参  数 : const char * press : 出版社
	//************************************
	bool SetBookPress(const ID id, const char* press);
	//************************************
	// 函数名 : SetBookDate
	// 功  能 : 设置指定编号的图书的出版日期
	// 返回值 : bool : 是否成功,未登录或出版日期过长会返回false
	// 参  数 : const ID id : 编号
	// 参  数 : const char * date : 出版日期
	//************************************
	bool SetBookDate(const ID id, const char* date);
	//************************************
	// 函数名 : SetBookType
	// 功  能 : 设置指定编号的图书的类型
	// 返回值 : bool : 是否成功,未登录或类型过长会返回false
	// 参  数 : const ID id : 编号
	// 参  数 : const char * type : 类型
	//************************************
	bool SetBookType(const ID id, const char* type);
	//************************************
	// 函数名 : GetBookRestCount
	// 功  能 : 获取指定编号的图书的馆内剩余量
	// 返回值 : unsigned int : 馆内剩余量,未登录或指定编号的图书不存在会返回0
	// 参  数 : const ID id : 编号
	//************************************
	unsigned int GetBookRestCount(const ID id)const;
	//************************************
	// 函数名 : GetBookTotalCount
	// 功  能 : 获取指定编号的图书的总量
	// 返回值 : unsigned int : 图书总量,未登录或指定编号的图书不存在会返回0
	// 参  数 : const ID id : 编号
	//************************************
	unsigned int GetBookTotalCount(const ID id)const;
	//************************************
	// 函数名 : GetAllBooks
	// 功  能 : 获取全部图书编号
	// 返回值 : std::list<ID> : 全部图书编号链表,未登录会返回空链表
	//************************************
	list<ID> GetAllBooks()const;
	//************************************
	// 函数名 : GetBorrowedBooks
	// 功  能 : 获取全部有借出的图书编号
	// 返回值 : std::list<ID> : 有借出的图书编号链表,未登录会返回空链表
	//************************************
	list<ID> GetBorrowedBooks()const;
	//************************************
	// 函数名 : GetNotBorrowedBooks
	// 功  能 : 获取全部未借出的图书编号
	// 返回值 : std::list<ID> : 未借出的图书编号链表,未登录会返回空链表
	//************************************
	list<ID> GetNotBorrowedBooks()const;
	//************************************
	// 函数名 : AddUser
	// 功  能 : 使用全部信息添加普通用户
	// 返回值 : bool : 是否成功
	// 参  数 : const ID id : 是否成功,未登录或用户已存在中或信息字符串过长会返回false
	// 参  数 : const char * name : 用户名
	// 参  数 : const char * password : 密码
	// 参  数 : const int gender : 性别
	// 参  数 : const int type : 类型
	//************************************
	bool AddUser(const ID id,
		const char * name,
		const char * password,
		const int gender,
		const int type);
	//************************************
	// 函数名 : RemoveUser
	// 功  能 : 删除指定编号的用户
	// 返回值 : bool : 是否成功,未登录或指定编号的用户不存在会返回false
	// 参  数 : const ID id : 用户编号
	//************************************
	bool RemoveUser(const ID id);
	//************************************
	// 函数名 : GetUserName
	// 功  能 : 获取指定编号的用户名
	// 返回值 : const char* : 用户名,未登录或指定编号的用户不存在会返回nullptr
	// 参  数 : const ID id : 编号
	//************************************
	const char* GetUserName(const ID id);
	//************************************
	// 函数名 : GetUserGender
	// 功  能 : 获取指定编号的用户性别
	// 返回值 : const char* : 性别,未登录或指定编号的用户不存在会返回nullptr
	// 参  数 : const ID id : 编号
	//************************************
	const char* GetUserGender(const ID id);
	//************************************
	// 函数名 : GetUserType
	// 功  能 : 获取指定编号的用户类型
	// 返回值 : const char* : 类型,未登录或指定编号的用户不存在会返回nullptr
	// 参  数 : const ID id : 编号
	//************************************
	const char* GetUserType(const ID id);
	//************************************
	// 函数名 : ReportLoss
	// 功  能 : 将指定编号的用户挂失,使其无法登录
	// 返回值 : bool : 是否成功,未登录或指定编号的用户不存在会返回false
	// 参  数 : const ID id : 编号
	//************************************
	bool ReportLoss(const ID id);
	//************************************
	// 函数名 : UndoReportLoss
	// 功  能 : 解除指定编号用户的挂失,使其能够登录
	// 返回值 : bool : 是否成功,未登录或指定编号的用户不存在会返回false
	// 参  数 : const ID id : 编号
	//************************************
	bool UndoReportLoss(const ID id);
	//************************************
	// 函数名 : Accept
	// 功  能 : 接收还书
	// 返回值 : bool : 是否成功,未登录或指定编号的用户不存在或指定编号的图书不存在会返回false
	// 参  数 : const ID userID : 用户编号
	// 参  数 : const ID bookID : 图书编号
	//************************************
	bool Accept(const ID userID, const ID bookID);
	//************************************
	// 函数名 : Save
	// 功  能 : 将图书管理员信息,用户信息和图书信息保存至文件
	// 返回值 : bool : 是否成功,未登录或文件保存失败会返回false
	//************************************
	bool Save()const;
	//************************************
	// 函数名 : FindBookByTitle
	// 功  能 : 按标题关键字查找图书
	// 返回值 : std::list<ID> : 图书编号链表,未登录会返回空链表
	// 参  数 : const char * title : 标题关键字
	//************************************
	list<ID> FindBookByTitle(const char* title)const;
	//list<ID> OverdueBookList()const;
private:
	//图书管理员信息文件路径
	const char*adminMapPath{ "admin" };
	//用户信息文件路径
	const char*userMapPath{ "user" };
	//书籍信息文件路径
	const char*bookMapPath{ "book" };
	////日志文件路径
	//const char*logPath{ "log.txt" };
	//最大借书时间
	const unsigned int overdueDays{ 90 };
	//是否登录
	bool Loggedin{ false };
	//图书管理员信息
	AdminMap adminMap{ AdminMap::ReadMap(adminMapPath) };
	//登录的图书管理员
	Admin admin{ Admin(0) };
	//用户信息
	UserMap userMap{ UserMap::ReadMap(userMapPath) };
	//书籍信息
	BookMap bookMap{ BookMap::ReadMap(bookMapPath) };
};

