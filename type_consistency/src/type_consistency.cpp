#define LUA_LIB
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
  #define LUA_BUILD_AS_DLL
#endif

#include <chrono>
#include <thread>
#include <iostream>

#include <qluacpp/qlua>

static struct luaL_reg ls_lib[] = {
  { NULL, NULL }
};

template <typename Table>
void test_getItem(qlua::api &q, std::function<void(const lua::entity<lua::type_policy<Table>>&)> f) {
  std::string table_name = ::qlua::table::detail::name_for_type<Table>::value();
  std::cout << "Table: ::qlua::table::" << table_name << std::endl;
  try {
    size_t n = q.getNumberOf<Table>();
    for (size_t i = 0; i < n; ++i) {
      try {
        using entity = const lua::entity<lua::type_policy<Table>>&;
        q.getItem<Table>(int(i), [&q, &f] (entity e) {
            f(e);
          });
      } catch (std::runtime_error e) {
        std::cout << "getItem<::qlua::table::" << table_name << ">: " << e.what() << std::endl;
      }
    }
  } catch (std::runtime_error e) {
    std::cout << "getNumberOf<::qlua::table::" << table_name << ">: " << e.what() << std::endl;
  }
}

#define TEST_TABLE_GETTER(FIELD)                \
  try {                                         \
    auto f = e().FIELD();                       \
  } catch (std::runtime_error e) {                                      \
    std::cout << "  " << #FIELD << ": " << e.what() << std::endl;       \
  }                                                                     \

#define TEST_TABLE_BEGIN(NAME)                  \
  auto test_##NAME = [] (const lua::entity<lua::type_policy<qlua::table::NAME>>& e) {


#define TEST_TABLE_END(NAME)                            \
  };                                                    \
  test_getItem<::qlua::table::NAME>(q, test_##NAME);    \



void test_tables(qlua::api& q) {
  TEST_TABLE_BEGIN(firms)
    TEST_TABLE_GETTER(firmid)
    TEST_TABLE_GETTER(firm_name)
    TEST_TABLE_GETTER(status)
    TEST_TABLE_GETTER(exchange)
    TEST_TABLE_END(firms)

    TEST_TABLE_BEGIN(classes)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(name)
TEST_TABLE_GETTER(code)
TEST_TABLE_GETTER(npars)
TEST_TABLE_GETTER(nsecs)
    TEST_TABLE_END(classes)

    TEST_TABLE_BEGIN(securities)
TEST_TABLE_GETTER(code)
TEST_TABLE_GETTER(name)
TEST_TABLE_GETTER(short_name)
TEST_TABLE_GETTER(class_code)
TEST_TABLE_GETTER(class_name)
TEST_TABLE_GETTER(face_value)
TEST_TABLE_GETTER(face_unit)
TEST_TABLE_GETTER(scale)
TEST_TABLE_GETTER(mat_date)
TEST_TABLE_GETTER(lot_size)
TEST_TABLE_GETTER(isin_code)
TEST_TABLE_GETTER(min_price_step)
    TEST_TABLE_END(securities)

    TEST_TABLE_BEGIN(trade_accounts)
TEST_TABLE_GETTER(class_codes)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(trdaccid)
TEST_TABLE_GETTER(description)
TEST_TABLE_GETTER(fullcoveredsell)
TEST_TABLE_GETTER(main_trdaccid)
TEST_TABLE_GETTER(bankid_t0)
TEST_TABLE_GETTER(bankid_tplus)
TEST_TABLE_GETTER(trdacc_type)
TEST_TABLE_GETTER(depunitid)
TEST_TABLE_GETTER(status)
TEST_TABLE_GETTER(firmuse)
TEST_TABLE_GETTER(depaccid)
TEST_TABLE_GETTER(bank_acc_id)
    //TEST_TABLE_GETTER(exec_market)
    TEST_TABLE_END(trade_accounts)

    TEST_TABLE_BEGIN(all_trades)
TEST_TABLE_GETTER(trade_num)
TEST_TABLE_GETTER(flags)
TEST_TABLE_GETTER(price)
TEST_TABLE_GETTER(qty)
TEST_TABLE_GETTER(value)
TEST_TABLE_GETTER(accruedint)
TEST_TABLE_GETTER(yield)
TEST_TABLE_GETTER(settlecode)
TEST_TABLE_GETTER(reporate)
TEST_TABLE_GETTER(repovalue)
TEST_TABLE_GETTER(repo2value)
TEST_TABLE_GETTER(repoterm)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(class_code)
TEST_TABLE_GETTER(datetime)
TEST_TABLE_GETTER(period)
TEST_TABLE_GETTER(open_interest)
TEST_TABLE_GETTER(exchange_code)
TEST_TABLE_GETTER(exec_market)
    TEST_TABLE_END(all_trades)

    TEST_TABLE_BEGIN(account_positions)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(currcode)
TEST_TABLE_GETTER(tag)
TEST_TABLE_GETTER(description)
TEST_TABLE_GETTER(openbal)
TEST_TABLE_GETTER(currentpos)
TEST_TABLE_GETTER(plannedpos)
TEST_TABLE_GETTER(limit1)
TEST_TABLE_GETTER(limit2)
TEST_TABLE_GETTER(orderbuy)
TEST_TABLE_GETTER(ordersell)
TEST_TABLE_GETTER(netto)
TEST_TABLE_GETTER(plannedbal)
TEST_TABLE_GETTER(debit)
TEST_TABLE_GETTER(credit)
TEST_TABLE_GETTER(bank_acc_id)
TEST_TABLE_GETTER(margincall)
TEST_TABLE_GETTER(settlebal)
    TEST_TABLE_END(account_positions)

    TEST_TABLE_BEGIN(orders)
TEST_TABLE_GETTER(order_num)
TEST_TABLE_GETTER(flags)
TEST_TABLE_GETTER(brokerref)
TEST_TABLE_GETTER(userid)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(account)
TEST_TABLE_GETTER(price)
TEST_TABLE_GETTER(qty)
TEST_TABLE_GETTER(balance)
TEST_TABLE_GETTER(value)
TEST_TABLE_GETTER(accruedint)
TEST_TABLE_GETTER(yield)
TEST_TABLE_GETTER(trans_id)
TEST_TABLE_GETTER(client_code)
TEST_TABLE_GETTER(price2)
TEST_TABLE_GETTER(settlecode)
TEST_TABLE_GETTER(uid)
TEST_TABLE_GETTER(canceled_uid)
TEST_TABLE_GETTER(exchange_code)
TEST_TABLE_GETTER(activation_time)
TEST_TABLE_GETTER(linkedorder)
TEST_TABLE_GETTER(expiry)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(class_code)
TEST_TABLE_GETTER(datetime)
TEST_TABLE_GETTER(withdraw_datetime)
TEST_TABLE_GETTER(bank_acc_id)
TEST_TABLE_GETTER(value_entry_type)
TEST_TABLE_GETTER(repoterm)
TEST_TABLE_GETTER(repovalue)
TEST_TABLE_GETTER(repo2value)
TEST_TABLE_GETTER(repo_value_balance)
TEST_TABLE_GETTER(start_discount)
TEST_TABLE_GETTER(reject_reason)
TEST_TABLE_GETTER(ext_order_flags)
TEST_TABLE_GETTER(min_qty)
TEST_TABLE_GETTER(exec_type)
TEST_TABLE_GETTER(side_qualifier)
TEST_TABLE_GETTER(acnt_type)
TEST_TABLE_GETTER(capacity)
TEST_TABLE_GETTER(passive_only_order)
TEST_TABLE_GETTER(visible)
    TEST_TABLE_END(orders)

    TEST_TABLE_BEGIN(futures_client_holding)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(trdaccid)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(type)
TEST_TABLE_GETTER(startbuy)
TEST_TABLE_GETTER(startsell)
TEST_TABLE_GETTER(startnet)
TEST_TABLE_GETTER(todaybuy)
TEST_TABLE_GETTER(todaysell)
TEST_TABLE_GETTER(totalnet)
TEST_TABLE_GETTER(openbuys)
TEST_TABLE_GETTER(opensells)
TEST_TABLE_GETTER(cbplused)
TEST_TABLE_GETTER(cbplplanned)
TEST_TABLE_GETTER(varmargin)
TEST_TABLE_GETTER(avrposnprice)
TEST_TABLE_GETTER(positionvalue)
TEST_TABLE_GETTER(real_varmargin)
TEST_TABLE_GETTER(total_varmargin)
TEST_TABLE_GETTER(session_status)
    TEST_TABLE_END(futures_client_holding)

    TEST_TABLE_BEGIN(futures_client_limits)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(trdaccid)
TEST_TABLE_GETTER(limit_type)
TEST_TABLE_GETTER(liquidity_coef)
TEST_TABLE_GETTER(cbp_prev_limit)
TEST_TABLE_GETTER(cbplimit)
TEST_TABLE_GETTER(cbplused)
TEST_TABLE_GETTER(cbplplanned)
TEST_TABLE_GETTER(varmargin)
TEST_TABLE_GETTER(accruedint)
TEST_TABLE_GETTER(cbplused_for_orders)
TEST_TABLE_GETTER(cbplused_for_positions)
TEST_TABLE_GETTER(options_premium)
TEST_TABLE_GETTER(ts_comission)
TEST_TABLE_GETTER(kgo)
TEST_TABLE_GETTER(currcode)
TEST_TABLE_GETTER(real_varmargin)
    TEST_TABLE_END(futures_client_limits)

    TEST_TABLE_BEGIN(money_limits)
TEST_TABLE_GETTER(currcode)
TEST_TABLE_GETTER(tag)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(client_code)
TEST_TABLE_GETTER(openbal)
TEST_TABLE_GETTER(openlimit)
TEST_TABLE_GETTER(currentbal)
TEST_TABLE_GETTER(currentlimit)
TEST_TABLE_GETTER(locked)
TEST_TABLE_GETTER(locked_value_coef)
TEST_TABLE_GETTER(locked_margin_value)
TEST_TABLE_GETTER(leverage)
TEST_TABLE_GETTER(limit_kind)
    TEST_TABLE_END(money_limits)

    TEST_TABLE_BEGIN(depo_limits)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(trdaccid)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(client_code)
TEST_TABLE_GETTER(openbal)
TEST_TABLE_GETTER(openlimit)
TEST_TABLE_GETTER(currentbal)
TEST_TABLE_GETTER(currentlimit)
TEST_TABLE_GETTER(locked_sell)
TEST_TABLE_GETTER(locked_buy)
TEST_TABLE_GETTER(locked_buy_value)
TEST_TABLE_GETTER(locked_sell_value)
TEST_TABLE_GETTER(wa_position_price)
TEST_TABLE_GETTER(limit_kind)
    TEST_TABLE_END(depo_limits)

    TEST_TABLE_BEGIN(trades)
TEST_TABLE_GETTER(trade_num)
TEST_TABLE_GETTER(order_num)
TEST_TABLE_GETTER(brokerref)
TEST_TABLE_GETTER(userid)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(canceled_uid)
TEST_TABLE_GETTER(account)
TEST_TABLE_GETTER(price)
TEST_TABLE_GETTER(qty)
TEST_TABLE_GETTER(value)
TEST_TABLE_GETTER(accruedint)
TEST_TABLE_GETTER(yield)
TEST_TABLE_GETTER(settlecode)
TEST_TABLE_GETTER(cpfirmid)
TEST_TABLE_GETTER(flags)
TEST_TABLE_GETTER(price2)
TEST_TABLE_GETTER(reporate)
TEST_TABLE_GETTER(client_code)
TEST_TABLE_GETTER(accrued2)
TEST_TABLE_GETTER(repoterm)
TEST_TABLE_GETTER(repovalue)
TEST_TABLE_GETTER(repo2value)
TEST_TABLE_GETTER(start_discount)
TEST_TABLE_GETTER(lower_discount)
TEST_TABLE_GETTER(upper_discount)
TEST_TABLE_GETTER(block_securities)
TEST_TABLE_GETTER(clearing_comission)
TEST_TABLE_GETTER(exchange_comission)
TEST_TABLE_GETTER(tech_center_comission)
TEST_TABLE_GETTER(settle_date)
TEST_TABLE_GETTER(settle_currency)
TEST_TABLE_GETTER(trade_currency)
TEST_TABLE_GETTER(exchange_code)
TEST_TABLE_GETTER(station_id)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(class_code)
TEST_TABLE_GETTER(datetime)
TEST_TABLE_GETTER(bank_acc_id)
TEST_TABLE_GETTER(broker_comission)
TEST_TABLE_GETTER(linked_trade)
TEST_TABLE_GETTER(period)
    TEST_TABLE_GETTER(trans_id)
TEST_TABLE_GETTER(kind)
TEST_TABLE_GETTER(clearing_bank_accid)
TEST_TABLE_GETTER(canceled_datetime)
TEST_TABLE_GETTER(clearing_firmid)
TEST_TABLE_GETTER(system_ref)
TEST_TABLE_GETTER(uid)

TEST_TABLE_GETTER(lseccode)
TEST_TABLE_GETTER(order_revision_number)
TEST_TABLE_GETTER(order_qty)
TEST_TABLE_GETTER(order_price)
TEST_TABLE_GETTER(order_exchange_code)
TEST_TABLE_GETTER(exec_market)
TEST_TABLE_GETTER(liquidity_indicator)
    TEST_TABLE_GETTER(extref)
TEST_TABLE_GETTER(ext_trade_flags)
TEST_TABLE_GETTER(on_behalf_of_uid)
TEST_TABLE_GETTER(client_qualifier)
TEST_TABLE_GETTER(client_short_code)
TEST_TABLE_GETTER(investment_decision_maker_qualifier)
TEST_TABLE_GETTER(investment_decision_maker_short_code)
TEST_TABLE_GETTER(executing_trader_qualifier)
TEST_TABLE_GETTER(executing_trader_short_code)
TEST_TABLE_GETTER(waiver_flag)
TEST_TABLE_GETTER(mleg_base_sid)
TEST_TABLE_GETTER(side_qualifier)
TEST_TABLE_GETTER(otc_post_trade_indicator)
TEST_TABLE_GETTER(capacity)
TEST_TABLE_GETTER(cross_rate)
    TEST_TABLE_END(trades)

    TEST_TABLE_BEGIN(stop_orders)
TEST_TABLE_GETTER(order_num)
TEST_TABLE_GETTER(ordertime)
TEST_TABLE_GETTER(flags)
TEST_TABLE_GETTER(brokerref)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(account)
TEST_TABLE_GETTER(condition)
TEST_TABLE_GETTER(condition_price)
TEST_TABLE_GETTER(price)
TEST_TABLE_GETTER(qty)
TEST_TABLE_GETTER(linkedorder)
TEST_TABLE_GETTER(expiry)
TEST_TABLE_GETTER(trans_id)
TEST_TABLE_GETTER(client_code)
TEST_TABLE_GETTER(co_order_num)
TEST_TABLE_GETTER(co_order_price)
TEST_TABLE_GETTER(stop_order_type)
TEST_TABLE_GETTER(orderdate)
TEST_TABLE_GETTER(alltrade_num)
TEST_TABLE_GETTER(stopflags)
TEST_TABLE_GETTER(offset)
TEST_TABLE_GETTER(spread)
TEST_TABLE_GETTER(balance)
TEST_TABLE_GETTER(uid)
TEST_TABLE_GETTER(filled_qty)
TEST_TABLE_GETTER(withdraw_time)
TEST_TABLE_GETTER(condition_price2)
TEST_TABLE_GETTER(active_from_time)
TEST_TABLE_GETTER(active_to_time)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(class_code)
TEST_TABLE_GETTER(condition_sec_code)
TEST_TABLE_GETTER(condition_class_code)
TEST_TABLE_GETTER(canceled_uid)
TEST_TABLE_GETTER(order_date_time)
TEST_TABLE_GETTER(withdraw_datetime)
    TEST_TABLE_END(stop_orders)

    TEST_TABLE_BEGIN(neg_deals)
TEST_TABLE_GETTER(neg_deal_num)
TEST_TABLE_GETTER(neg_deal_time)
TEST_TABLE_GETTER(flags)
TEST_TABLE_GETTER(brokerref)
TEST_TABLE_GETTER(userid)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(cpuserid)
TEST_TABLE_GETTER(cpfirmid)
TEST_TABLE_GETTER(account)
TEST_TABLE_GETTER(price)
TEST_TABLE_GETTER(qty)
TEST_TABLE_GETTER(matchref)
TEST_TABLE_GETTER(settlecode)
TEST_TABLE_GETTER(yield)
TEST_TABLE_GETTER(accruedint)
TEST_TABLE_GETTER(value)
TEST_TABLE_GETTER(price2)
TEST_TABLE_GETTER(reporate)
TEST_TABLE_GETTER(refundrate)
TEST_TABLE_GETTER(trans_id)
TEST_TABLE_GETTER(client_code)
TEST_TABLE_GETTER(repoentry)
TEST_TABLE_GETTER(repovalue)
TEST_TABLE_GETTER(repo2value)
TEST_TABLE_GETTER(repoterm)
TEST_TABLE_GETTER(start_discount)
TEST_TABLE_GETTER(lower_discount)
TEST_TABLE_GETTER(upper_discount)
TEST_TABLE_GETTER(block_securities)
TEST_TABLE_GETTER(uid)
TEST_TABLE_GETTER(withdraw_time)
TEST_TABLE_GETTER(neg_deal_date)
TEST_TABLE_GETTER(balance)
TEST_TABLE_GETTER(origin_repovalue)
TEST_TABLE_GETTER(origin_qty)
TEST_TABLE_GETTER(origin_discount)
TEST_TABLE_GETTER(neg_deal_activation_date)
TEST_TABLE_GETTER(neg_deal_activation_time)
TEST_TABLE_GETTER(quoteno)
TEST_TABLE_GETTER(settle_currency)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(class_code)
TEST_TABLE_GETTER(bank_acc_id)
TEST_TABLE_GETTER(withdraw_date)
TEST_TABLE_GETTER(linkedorder)
TEST_TABLE_GETTER(activation_date_time)
TEST_TABLE_GETTER(withdraw_date_time)
TEST_TABLE_GETTER(date_time)
    TEST_TABLE_END(neg_deals)

    TEST_TABLE_BEGIN(neg_trades)
TEST_TABLE_GETTER(trade_num)
TEST_TABLE_GETTER(trade_date)
TEST_TABLE_GETTER(settle_date)
TEST_TABLE_GETTER(flags)
TEST_TABLE_GETTER(brokerref)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(account)
TEST_TABLE_GETTER(cpfirmid)
TEST_TABLE_GETTER(cpaccount)
TEST_TABLE_GETTER(price)
TEST_TABLE_GETTER(qty)
TEST_TABLE_GETTER(value)
TEST_TABLE_GETTER(settlecode)
TEST_TABLE_GETTER(report_num)
TEST_TABLE_GETTER(cpreport_num)
TEST_TABLE_GETTER(accruedint)
TEST_TABLE_GETTER(repotradeno)
TEST_TABLE_GETTER(price1)
TEST_TABLE_GETTER(reporate)
TEST_TABLE_GETTER(price2)
TEST_TABLE_GETTER(client_code)
TEST_TABLE_GETTER(ts_comission)
TEST_TABLE_GETTER(balance)
TEST_TABLE_GETTER(settle_time)
TEST_TABLE_GETTER(amount)
TEST_TABLE_GETTER(repovalue)
TEST_TABLE_GETTER(repoterm)
TEST_TABLE_GETTER(repo2value)
TEST_TABLE_GETTER(return_value)
TEST_TABLE_GETTER(discount)
TEST_TABLE_GETTER(lower_discount)
TEST_TABLE_GETTER(upper_discount)
TEST_TABLE_GETTER(block_securities)
TEST_TABLE_GETTER(urgency_flag)
TEST_TABLE_GETTER(type)
TEST_TABLE_GETTER(operation_type)
TEST_TABLE_GETTER(expected_discount)
TEST_TABLE_GETTER(expected_quantity)
TEST_TABLE_GETTER(expected_repovalue)
TEST_TABLE_GETTER(expected_repo2value)
TEST_TABLE_GETTER(expected_return_value)
TEST_TABLE_GETTER(order_num)
TEST_TABLE_GETTER(report_trade_date)
TEST_TABLE_GETTER(settled)
TEST_TABLE_GETTER(clearing_type)
TEST_TABLE_GETTER(report_comission)
TEST_TABLE_GETTER(coupon_payment)
TEST_TABLE_GETTER(principal_payment)
TEST_TABLE_GETTER(principal_payment_date)
TEST_TABLE_GETTER(nextdaysettle)
TEST_TABLE_GETTER(settle_currency)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(class_code)
TEST_TABLE_GETTER(compval)
TEST_TABLE_GETTER(parenttradeno)
TEST_TABLE_GETTER(bankid)
TEST_TABLE_GETTER(bankaccid)
TEST_TABLE_GETTER(precisebalance)
TEST_TABLE_GETTER(confirmtime)
TEST_TABLE_GETTER(ex_flags)
TEST_TABLE_GETTER(confirmreport)
    TEST_TABLE_END(neg_deals)


    TEST_TABLE_BEGIN(neg_deal_reports)
TEST_TABLE_GETTER(report_num)
TEST_TABLE_GETTER(report_date)
TEST_TABLE_GETTER(flags)
TEST_TABLE_GETTER(userid)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(account)
TEST_TABLE_GETTER(cpfirmid)
TEST_TABLE_GETTER(cpaccount)
TEST_TABLE_GETTER(qty)
TEST_TABLE_GETTER(value)
TEST_TABLE_GETTER(withdraw_time)
TEST_TABLE_GETTER(report_type)
TEST_TABLE_GETTER(report_kind)
TEST_TABLE_GETTER(commission)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(class_code)
TEST_TABLE_GETTER(report_time)
TEST_TABLE_GETTER(report_date_time)
    TEST_TABLE_END(neg_deal_reports)

        TEST_TABLE_BEGIN(firm_holding)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(openbal)
TEST_TABLE_GETTER(currentpos)
TEST_TABLE_GETTER(plannedposbuy)
TEST_TABLE_GETTER(plannedpossell)
TEST_TABLE_GETTER(usqtyb)
TEST_TABLE_GETTER(usqtys)
    TEST_TABLE_END(firm_holding)

    TEST_TABLE_BEGIN(account_balance)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(trdaccid)
TEST_TABLE_GETTER(depaccid)
TEST_TABLE_GETTER(openbal)
TEST_TABLE_GETTER(currentpos)
TEST_TABLE_GETTER(plannedpossell)
TEST_TABLE_GETTER(plannedposbuy)
TEST_TABLE_GETTER(planbal)
TEST_TABLE_GETTER(usqtyb)
TEST_TABLE_GETTER(usqtys)
TEST_TABLE_GETTER(planned)
TEST_TABLE_GETTER(settlebal)
TEST_TABLE_GETTER(bank_acc_id)
TEST_TABLE_GETTER(firmuse)
    TEST_TABLE_END(account_balance)

    TEST_TABLE_BEGIN(ccp_holdings)
TEST_TABLE_GETTER(firmid)
TEST_TABLE_GETTER(depo_account)
TEST_TABLE_GETTER(account)
TEST_TABLE_GETTER(bank_acc_id)
TEST_TABLE_GETTER(settle_date)
TEST_TABLE_GETTER(qty)
TEST_TABLE_GETTER(qty_buy)
TEST_TABLE_GETTER(qty_sell)
TEST_TABLE_GETTER(netto)
TEST_TABLE_GETTER(debit)
TEST_TABLE_GETTER(credit)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(class_code)
TEST_TABLE_GETTER(planned_covered)
                                                       TEST_TABLE_GETTER(firm_use)
    TEST_TABLE_END(ccp_holdings)
    
    TEST_TABLE_BEGIN(rm_holdings)
TEST_TABLE_GETTER(sec_code)
TEST_TABLE_GETTER(class_code)
TEST_TABLE_GETTER(firmId)
TEST_TABLE_GETTER(account)
TEST_TABLE_GETTER(bank_acc_id)
TEST_TABLE_GETTER(date)
TEST_TABLE_GETTER(debit)
TEST_TABLE_GETTER(credit)
TEST_TABLE_GETTER(value_buy)
TEST_TABLE_GETTER(value_sell)
TEST_TABLE_GETTER(margin_call)
TEST_TABLE_GETTER(planned_covered)
TEST_TABLE_GETTER(debit_balance)
TEST_TABLE_GETTER(credit_balance)
    TEST_TABLE_END(rm_holdings)
    
}

void my_main(lua::state& l) {
  using namespace std::chrono_literals;
  qlua::api q(l);
  test_tables(q);
  q.message("type consistency: Waiting for callbacks");
  for (int i = 0; i < 25; ++i) {
    std::this_thread::sleep_for(1s);
  }
  q.message("type consistency: Terminating main handler");
}

std::tuple<int> OnStop(const lua::state& l,
                       ::lua::entity<::lua::type_policy<int>> signal) {
  return std::make_tuple(int(0));
}

void OnTransReply(const lua::state& l,
                  ::lua::entity<::lua::type_policy<::qlua::table::trans_reply>> reply) {
  std::cout << "OnTransReply" << std::endl;
}

LUACPP_STATIC_FUNCTION2(main, my_main)
LUACPP_STATIC_FUNCTION3(OnStop, OnStop, int)
LUACPP_STATIC_FUNCTION3(OnTransReply, OnTransReply, ::qlua::table::trans_reply)

extern "C" {
  LUALIB_API int luaopen_lualib_type_consistency(lua_State *L) {
    lua::state l(L);

    ::lua::function::main().register_in_lua(l, my_main);
    ::lua::function::OnTransReply().register_in_lua(l, OnTransReply);

    luaL_openlib(L, "lualib_type_consistency", ls_lib, 0);
    return 0;
  }
}
