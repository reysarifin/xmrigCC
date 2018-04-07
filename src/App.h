/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2016-2017 XMRig       <support@xmrig.com>
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __APP_H__
#define __APP_H__


#include <uv.h>


#include "interfaces/IConsoleListener.h"


class Console;
class Httpd;
class Network;
class Options;
class CCClient;

class App : public IConsoleListener
{
public:
  App(int argc, char **argv);
  ~App();

  int start();

  static void restart();
  static void shutdown();

protected:
  void onConsoleCommand(char command) override;

private:
  void background();
  void stop(bool restart);

  static void onSignal(uv_signal_t* handle, int signum);
  static void onCommandReceived(uv_async_t* handle);

  static App *m_self;

  bool m_restart;

  Console *m_console;
  Httpd *m_httpd;
  Network *m_network;
  Options *m_options;
  uv_signal_t m_sigHUP;
  uv_signal_t m_sigINT;
  uv_signal_t m_sigTERM;
  CCClient *m_ccclient;
  uv_async_t m_async;
};


#endif /* __APP_H__ */
