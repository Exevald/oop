#pragma once

#include "CActor.h"
#include <random>

namespace
{
int GenerateRandomInt(int maxValue)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, maxValue);

	return dist(gen);
}
} // namespace

class Homer : public CActorWithBankAccount
{
public:
	explicit Homer(Money cash, AccountId accountId, CBank& bank)
		: CActorWithBankAccount(cash, accountId, bank)
	{
	}

	void Act(Actors& actors) override
	{
		if (Homer::SendMoney(actors.marge->GetAccountId(), 250))
		{
			std::cout << "Homer sent money to Marge's card\n";
		}
		if (Homer::SendMoney(actors.mrBurns->GetAccountId(), 500))
		{
			std::cout << "Homer paid for electricity\n";
		}
		if (Homer::WithdrawMoney(100))
		{
			if (Homer::SendCash(*actors.bart, 50))
			{
				std::cout << "Homer gave cash to Bart\n";
			}
			if (Homer::SendCash(*actors.lisa, 50))
			{
				std::cout << "Homer gave cash to Lisa\n";
			}
		}
	}
};

class Marge : public CActorWithBankAccount
{
public:
	explicit Marge(Money cash, AccountId accountId, CBank& bank)
		: CActorWithBankAccount(cash, accountId, bank)
	{
	}

	void Act(Actors& actors) override
	{
		if (Marge::SendMoney(actors.apu->GetAccountId(), 250))
		{
			std::cout << "Marge paid for Apu's products\n";
		}
	}
};

class Bart : public CActor
{
public:
	explicit Bart(Money cash)
		: CActor(cash)
	{
	}

	void Act(Actors& actors) override
	{
		if (Bart::SendCash(*actors.apu, 25))
		{
			std::cout << "Bart paid for Apu's products\n";
		}
	}
};

class Lisa : public CActor
{
public:
	explicit Lisa(Money cash)
		: CActor(cash)
	{
	}

	void Act(Actors& actors) override
	{
		if (Lisa::SendCash(*actors.apu, 25))
		{
			std::cout << "Lisa paid for Apu's products\n";
		}
	}
};

class Apu : public CActorWithBankAccount
{
public:
	explicit Apu(Money cash, AccountId accountId, CBank& bank)
		: CActorWithBankAccount(cash, accountId, bank)
	{
	}

	void Act(Actors& actors) override
	{
		if (Apu::SendMoney(actors.mrBurns->GetAccountId(), 700))
		{
			std::cout << "Apu paid for electricity\n";
		}
		if (Apu::GetCash() > 0)
		{
			if (Apu::DepositMoney(Apu::GetCash()))
			{
				std::cout << "Apu deposited money to his bank account\n";
			}
		}
	}
};

class MrBurns : public CActorWithBankAccount
{
public:
	explicit MrBurns(Money cash, AccountId accountId, CBank& bank)
		: CActorWithBankAccount(cash, accountId, bank)
	{
	}

	void Act(Actors& actors) override
	{
		if (MrBurns::SendMoney(actors.homer->GetAccountId(), 850))
		{
			std::cout << "Mr. Burns paid Homer for his work\n";
		}
		if (MrBurns::SendMoney(actors.smithers->GetAccountId(), 350))
		{
			std::cout << "Mr. Burns paid Smithers for his work\n";
		}
	}
};

class Nelson : public CActor
{
public:
	explicit Nelson(Money cash)
		: CActor(cash)
	{
	}

	void Act(Actors& actors) override
	{
		Money stolenAmount = GenerateRandomInt(50);

		if (Nelson::StealCash(*actors.bart, stolenAmount))
		{
			std::cout << "Nelson stole Bart's cash\n";
			if (Nelson::SendCash(*actors.apu, stolenAmount))
			{
				std::cout << "Nelson paid for Apu's cigarettes\n";
			}
		}
	}
};

class Snake : public CActorWithBankAccount
{
public:
	explicit Snake(Money cash, AccountId accountId, CBank& bank)
		: CActorWithBankAccount(cash, accountId, bank)
	{
	}

	void Act(Actors& actors) override
	{
		if (Snake::StealMoney(actors.homer->GetAccountId(), 100))
		{
			std::cout << "Snake stole money from Homer's bank account\n";
		}
	}
};

class Smithers : public CActorWithBankAccount
{
public:
	explicit Smithers(Money cash, AccountId accountId, CBank& bank)
		: CActorWithBankAccount(cash, accountId, bank)
	{
	}

	void Act(Actors& actors) override
	{
		if (Smithers::SendMoney(actors.apu->GetAccountId(), 150))
		{
			std::cout << "Smithers paid for Apu's products\n";
		}

		int isBankAccountRecreated = GenerateRandomInt(1);
		if (isBankAccountRecreated)
		{
			auto cash = Smithers::CloseAccount();
			Smithers::OpenAccount();
			if (Smithers::DepositMoney(cash))
			{
				std::cout << "Smithers recreated his bank account\n";
			}
		}
	}
};